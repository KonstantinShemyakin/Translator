#include <ak/config.h>
#define Uses_ot
#include <ot/ot.h>
#pragma hdrstop
#include <ot/_simple.h>
#include <ot/_trans.h>
#include <db/types.h>

#if (__FLORA_DEBUG>0)
   #define FLORA_TRANSLATOR_DUMP_LEVEL_IF(LEVEL,DATA) if (translator->dumpLevel>LEVEL) { DATA; }
#else
   #define FLORA_TRANSLATOR_DUMP_LEVEL_IF(LEVEL,DATA)
#endif

#define MAXDWORD 0xffffffff

using namespace flora;

const int localDimension = 1000;

//*********************************************************************
bool  TOtProgram::translate(TOtTranslateMessArray* mess)
{
   if (executing)  {
      if (mess)  {
         mess->add(TOtTranslateMessage::tError,lexMess_WriteOnRun.system(),0,0,this);
         }
//      translated=false;
      return false;
      }
   ACCESS_WRITER_HOLD(this);
   TOtTranslator *translator;
   if (mess && mess->translator) 
      translator=mess->translator;
   else
      translator=new TOtTranslator();
   TOtTranslateMessArray messMy;
   TOtTranslateMessArray* mess_;
   if (mess) {
      messMy.entourage(mess->stack);
      }
   bool  old_translated = translated;
   TTime old_build_time = build_time;
   TStr  old_username   = username;

   resetProgram();
   mess_=&messMy;
   translator->setLanguage(getLanguage());
   FLORA_TRANSLATOR_DUMP_LEVEL_IF(0,
      TString name_;
      TOtNode *owner=getOwnerNode();
      if (owner)
         name_=owner->getFullName();
      TOtNode *pn=OT_DOWNCAST(this,TOtNode);
      if (!pn)
         name_+=getName();
      translator->os<<endl<<"**************** "<<name_<<endl;
      for(int i=1; i<=getVarCount(); i++) {
         TOtVar* v=getVar(i);
         TString s(" ");
         s+=v->objectTypeName(); s+=":"; s.padTrail(26);
         s+=v->getName();
         TOtVarPtr* varPtr=OT_DOWNCAST(v,TOtVarPtr);
         if (varPtr) {
            TString initialPath=varPtr->initialPath;
            s.padTrail(50);
            s+=initialPath;
            }
         TOtRef* ref=OT_DOWNCAST(v,TOtRef);
         if (ref) {
            TString srcPath=ref->getPath();
            s.padTrail(50);
            s+=srcPath;
            }
         translator->os<<s<<endl;
         }
      if ( getVarCount()==0 )
         translator->os<<TStr("================================ Пусто ===============================").fromUTF8()<<endl;
      else
         translator->os<<"======================================================================"<<endl;
      translator->printSource(translator->os,this);
      translator->os<<"----------------------------------------------------------------------"<<endl;
      )
 
   translator->translate(this,mess_);

   if (mess)  {
      for (int i=messMy.low(); i<=messMy.last(); i++) {
         TOtTranslateMessage& we=messMy[i];
         if (!we.src)
            we.src=this;
         }
      for (int i=messMy.low(); i<=messMy.last(); i++) {
         const TOtTranslateMessage& we=messMy[i];
         if (we.type==TOtTranslateMessage::tError)
            mess->add(we);
         }
      for (int i=messMy.low(); i<=messMy.last(); i++) {
         const TOtTranslateMessage& we=messMy[i];
         if (we.type==TOtTranslateMessage::tWarning)
            mess->add(we);
         }
      }

   FLORA_TRANSLATOR_DUMP_LEVEL_IF(0,
      for (int m=messMy.low();m<=messMy.last();m++) {
         const TOtTranslateMessage& we=messMy[m];
         TString s;
         if (we.type==TOtTranslateMessage::tWarning)
            s+="Warning ";
         else if (we.type==TOtTranslateMessage::tError)
            s+="Error   ";
         s+=intToStr(we.pos);
         s.padTrail(16);
         s+=" : ";
         s+=we.text;
         translator->os<<s<<endl;
         }
      )
   if (translator->errCount)
      resetProgram();
   else
      translated=true;
   if (mess && mess->translator) 
      translator->clear();
   else
      delete translator;
   if (old_translated && translated) {
      build_time = old_build_time;
      username   = old_username;
      }
   else {
      build_time = systemClock.currTime();
      username   = getDeveloperName();
      }
   return translated;
}

void TOtTranslator::errorFuncNotFind(const TOtFuncFinder& finder, const TOtLexem& l)
{
   TString mess;
   switch (finder.mismatch) {
      case TOtFuncSelector::mmAccess    : mess = lexMess_AccessDenied.system();       break;
      case TOtFuncSelector::mmInherited : mess = lexMess_EndInherited.system();       break;
      case TOtFuncSelector::mmParam     : mess = lexMess_InvalidParameters.system();  break;
      case TOtFuncSelector::mmResult    : mess = lexMess_InvalidResult.system();      break;
      case TOtFuncSelector::mmCount     : mess = lexMess_BadCountParameters.system(); break;
      case TOtFuncSelector::mmObsolete  : mess = lexMess_WarningFuncObsolete.system();break;
      default :                           mess = lexMess_UnknownIdentify.system();    break;
      }
   int pos = 0;
   if (finder.mismatch == TOtFuncSelector::mmParam)  {
      mess << '('; mess << intToStr(finder.gut_param + 1); mess << ')';
      if (finder.castable && (finder.castable->tokens.inside(finder.gut_param)))  {
         int token = finder.castable->tokens[finder.gut_param].token;
         if (codes.inside(token)) pos = codes[token].pos;
         }
      }
   mess << ' ' << getText(l);
   if (pos) { error(mess,pos); } else { error(mess,l); }
}

TString TOtTranslator::denial_text(TOtObject *obj) const
{
   TString err_text;
   int denial = program->denial(obj, TOtObject::pmInternal | TOtObject::pmProtected | TOtObject::pmPrivate | TOtObject::pmInaccessible, NULL);
   if (denial & (TOtObject::pmProtected | TOtObject::pmPrivate     )) { err_text += lexMess_AccessDenied.system(); }
   if (denial & (TOtObject::pmInternal  | TOtObject::pmInaccessible)) { err_text += lexMess_Inaccessible.system(); }
   return err_text; 
}
bool TOtTranslator::denial_error(TOtObject *obj)
{
   if (obj->deprecated) { warning(lexMess_WarningDeprecated.system()); }
   TString err_text = denial_text(obj);
   if (err_text != EMPTY_STR) { error(err_text); return true; } else return false;
}

#if (__FLORA_DEBUG>0)
OTIMPEXP TString TOtTranslator::debugFile("dump");
#endif

TOtFuncFinderHolder::TOtFuncFinderHolder(TOtFuncFinderCollection& own)
   :owner(&own)
{
   item = owner->create();
} 
TOtFuncFinderHolder::TOtFuncFinderHolder(TOtFuncFinderHolder& join)
   :owner(join.owner)
{
   item = join.item; join.owner=NULL;
}
TOtFuncFinderHolder::~TOtFuncFinderHolder()
{
   if (owner) owner->del(item);
} 

void TOtFuncFinderHolder::tune(TOtObject* o, int beg, int lek) 
{ 
   item->context=o; item->c.beg=beg; item->c.end=beg; item->c.lek=lek;
}


TOtFuncFinder::TOtFuncFinder()
   :TOtFuncSelector(&p,NULL,&c), index(0)
{
}

void TOtFuncFinder::param(const TOtType& type, int token)
{
   p.param.add(type); c.addToken(token);
}
void TOtFuncFinder::prepend(const TOtType& type)
{
   p.param.insert(p.param.low(),type);
   TOtFuncCast::TTokenItem item; item.token=c.beg;
   c.tokens.insert(c.tokens.low(),item);
}

void TOtFuncFinder::save()
{
   _p=p; _c=c;
}
void TOtFuncFinder::restore()
{
   p=_p; c=_c;
}

void TOtFuncFinder::total(const TOtFuncFinder& join)
{
   p=join.p; c=join.c;
}
void TOtFuncFinder::total(const TOtFuncProfile& profile_)
{
   TOtType result=profile_.result();
   if (p.param.count() && (result!=TOtType::Void)) {
      int attr=profile_.attr();
      const TOtType &typeLow=p.param[p.param.low()];
      if (!(attr&TSimpleOperation::cYesArray) && (attr&(TSimpleOperation::cSetTypePtr|TSimpleOperation::cCastTypePtr|TSimpleOperation::cItemDocList)) && (typeLow.id!=id_NULL)) {
         result.oblique=typeLow.oblique;
         if (!(attr&TSimpleOperation::cItemDocList)) {
            result.origin=typeLow.origin;
            }
         result.templateName=typeLow.templateName;
         }
      }
   total(result);
}
void TOtFuncFinder::total(const TOtType& type)
{
   result(type);
   c.casts=bestCast.casts;
   for (int i=c.tokens.low();i<=c.tokens.last();i++) {
      if (i>c.casts.last()) { TCastItem item; c.casts.add(item); }
      }
}
void TOtFuncFinder::result(const TOtType& type)
{
   p.result(type); c.result=type;
}
const TOtType& TOtFuncFinder::result() const
{
   return c.result;
}

void TOtFuncFinder::attach(TProgramTable::TFuncPtr& func, const TOtFuncProfile& profile_) const
{
   func.profile_.attach(new TOtFuncProfile(profile_));
   if (!(profile_.attr()&TOtFuncProfile::faLibrary) || profile_.isEllipsis() || profile_.isMethod()) return;
   int func_default = profile_.defaults.count();
   int func_param = profile_.param.count();
   int fact_param = p.param.count();
   if ((func_param > fact_param) && ((func_param - fact_param) <= func_default)) {
      while (func.profile_.count() > fact_param) { func.profile_.removeLast(); }
      }
}

void TOtFuncFinder::clear()
{
   //TRelate
   relate.mode=rltNode; relate.templateName.clear();

   p.clear(); c.clear(); _p.clear(); _c.clear();
   profile=&p; castable=&c;
   //TOtFuncSelector::clear();
   TOtFuncSelector::reset();
   space=NULL; pointer=NULL;
   templateDefinition=NULL;
   clear_mismatch();
   checkContactRelative=false;disableConversion=false;withoutObsolete=false;checkDefaultParam=true;
   //TOtFuncDemand::clear();
   templateType=id_unknown;;
   context=NULL;
} 

TOtFuncFinderCollection::~TOtFuncFinderCollection()
{
   TOtFuncFinder *item;
   while (!empty()) {
      pop(item); delete item;
      }
}
static int FuncFinderCount=0;
TOtFuncFinder* TOtFuncFinderCollection::create()
{
   FuncFinderCount++;
   TOtFuncFinder *item;
   if (empty()) {
      item = new TOtFuncFinder();
      }
   else {
      pop(item);
      }
   item->withoutObsolete=true;
   return item;
}
void TOtFuncFinderCollection::del(TOtFuncFinder *item)
{
   item->clear();
   push(item);
}

#define CONFORMANCE
/*-----------------------  Рекурсивный разбор ------------------------*/
TOtTranslator::TOtTranslator()
   :stack(10,10),property(1,10,-20),adventurers(10,-20),
    codes(1,150,-20),lineToken(0),nesting(0),
    locVar(this,10,10),numLiter(15,-10),intLiter(15,-10),dumpLevel(0),types(15,-10),this_type_index(0),
    indexMain(0),indexPath(0),indexFunc(0),indexThis(0),indexNODE(0),indexTHIS(0),indexROOT(0),
    indexTemplate(0),indexNamespace(0),paramtypes(1,8,-20),cases(1,0,-20)
{
 #if (__FLORA_DEBUG>0)
   T_PtrOt<TOtObjectStr> debugStr=OT_DOWNCAST((*TOtNode::root()).find("/Desktop/debug"),TOtObjectStr);
   if (debugStr) {
      debugFile=debugStr->get();
      if (debugFile.len()) {
         os.open(debugFile,ios::out | ios::ate);
         if (!(os.rdstate() & (ios::failbit | ios::badbit))) {
            dumpLevel=1;
            if (debugFile=="dump")
               dumpLevel=2;
            else if (debugFile=="dump_all")
               dumpLevel=3;
            }
         }
      }
   else {
      dumpLevel=0;
      }
 #endif
}

void TOtTranslator::translate(TOtProgram *u, TOtTranslateMessArray* mess)
{
   errCount=0;
   errMess=mess;
   program=u;
   program->table.attach(new TProgramTable());
#if defined(PROGRAM_MINIMUM_TYPE_FIELD)
   field_info_table.set(this);
#endif

   defines.push(ppParse);
   TOtParse::parse(program->getSource(),u,mess);
   blocks.setTranslator(this);
   gotoBackward.setProgram(&(codes));
   gotoForward .setProgram(&(codes));
   gotoLabel1  .setProgram(&(codes));
   gotoLabel2  .setProgram(&(codes));
   trueChain   .setProgram(&(codes));
   falseChain  .setProgram(&(codes));
   nCompaund=0;

   int lSource=(int)program->getSource().len();
   if (lSource > 5000) {
      codes.setLimit(lSource/3);
      }

   locStruct.program=program;
   locStruct.translator=this;

   {
   TLocStruct& loc=locStruct.create(indexMain);
   loc.isMain=true; loc.isOpen=true;
   }{
   TLocStruct& loc=locStruct.create(indexPath);
   loc.isMain=true; loc.isOpen=true;
   }{
   TLocStruct& loc=locStruct.create(indexTemplate);
   loc.isMain=true; loc.isOpen=true;
   }{
   TLocStruct& loc=locStruct.create(indexNamespace);
   loc.isMain=true; loc.isOpen=true;
   }

   indexThis=indexNODE=indexTHIS=indexROOT=0;
   if (node) {
      TLocStruct& loc=locStruct.create(indexNODE);
      loc.isReferenc=true;
      loc.isPath=true;
      loc.obj=node;
      loc.path=loc.obj->getName();
      if (loc.path.len()) loc.isConst=true;
      loc.relate=TProgramTable::TFieldPtr::rltNode;
      TOtType type=loc.obj->objectType();
      loc.isChild=TOtMetaInfo::castable(type.id,id_TOtNode);
      loc.setType(type);
      loc.link=addField(type,loc.path,TProgramTable::TFieldPtr::fldPath,loc.relate);

      dirTemplate=program->getTemplateMaster(true);
      if (dirTemplate) {
         TLocStruct& loc2=locStruct.create(indexThis);
         loc2.isReferenc=true;
         loc2.isConst=true;
         loc2.isPath=true;
         loc2.obj=dirTemplate;
         loc2.relate=TProgramTable::TFieldPtr::rltThis;
         TOtType type2=loc2.obj->objectType();
         loc2.isChild=TOtMetaInfo::castable(type2.id,id_TOtNode);
         loc2.setType(type2);
         loc2.link=addField(type2,loc2.path,TProgramTable::TFieldPtr::fldPath,loc2.relate);
         }
      }

   {
   TLocStruct& loc=locStruct.create(indexTHIS);
   loc.isReferenc=true;
   loc.isPath=true;
   loc.obj=program;
   loc.path=loc.obj->getName();
   if (loc.path.len() && (OT_DOWNCAST(loc.obj,TOtNode))) loc.isConst=true;
   loc.relate=TProgramTable::TFieldPtr::rltNode;
   TOtType type=loc.obj->objectType();
   loc.isChild=TOtMetaInfo::castable(type.id,id_TOtNode);
   loc.setType(type);
   loc.link=addField(type,loc.path,TProgramTable::TFieldPtr::fldPath,loc.relate);
   }{
   TLocStruct& loc=locStruct.create(indexROOT);
   loc.isReferenc=true;
   loc.isConst=true;
   loc.isPath=true;
   loc.path="/";
   loc.obj=TOtNode::root();
   loc.isChild=true;
   loc.setType(loc.obj->objectType());
   loc.link=addField(loc.getType(),loc.path,TProgramTable::TFieldPtr::fldPath,loc.relate);
   }

   bool member=false;
   TOtAFunc *func=OT_DOWNCAST(program,TOtAFunc);

   if (func) {
      member=func->isMethod();
      }
   if (member && !indexThis) {
      error(TString(lexMess_CantFindObject.system())+" : this");
      errCount++;
      }

   paramtypes.low(program->var.low());
   for (int i=1; i<=program->getVarObjectCount(); i++ ) {
      TPtrOtObject var=program->getVarObject(i);
      TOtType temp=var->objectType();
      if (TOtMetaInfo::castable(temp.origin,id_TOtDir) && temp.templateName.len()) {
         int k;
         if (!findTemplateWithError(temp.templateName,k,lex)) {
            errCount++;
            }
         if (!TOtMetaInfo::castableToL(temp)) k*=-1;
         paramtypes.add(k);
         }
      else
         paramtypes.add(0);
      }

   T_PtrOt<TOtMainProgram> mp=new TOtMainProgram();
   mp->setStatus(TOtObject::stStarted);
   mp->execStart();
   stackExec=mp->getMyStack();
   u->catches.clear();
   { TOtProgram::TCatch item(1                 ,0);  u->catches.add(item); }
   { TOtProgram::TCatch item(exRangeCheckError ,0);  u->catches.add(item); }
   { TOtProgram::TCatch item(1                 ,0);  u->catches.add(item); }
   { TOtProgram::TCatch item(exUseOfNullPointer,0);  u->catches.add(item); }
   mp->pushTry(u,stackExec,1);

 //   if (heapcheck()<0)
 //     EX_MESSAGE("Internal error: heap corrupted");
   if (!errCount) {
      statements();
      }

   defines.pop();
/*
   const TLocStruct& locMain=locStruct[indexMain];
   const TLocStruct& locTemplate=locStruct[indexTemplate];
   const TLocStruct& locNamespace=locStruct[indexNamespace];
   DEBUG_LOG(-1,"main " << intToStr(locMain.count(),6,10,' ') << " template " << intToStr(locTemplate.count(),6,10,' ') << " namespace " << intToStr(locNamespace.count(),6,10,' ') << " program " << program->getFullName())
*/
   FLORA_TRANSLATOR_DUMP_IF(1, printStack(os); print(os,false); )
   FLORA_TRANSLATOR_DUMP_IF(2, debug.print(os); )
   if (!errCount && !endPos) {
      if (!codes.empty()) {
         optimizeCast(*stackExec,codes.low(),codes.last());
         }
      optimize();
      FLORA_TRANSLATOR_DUMP_IF(0, print(os,true); )
      }
   if (endPos) endPos=lex.ofsMain()+1;

   mp->popTry();
   mp->execFinish();
}

void TOtTranslator::clear()
{
   TLocStruct& locMain     =locStruct[indexMain     ]; locStruct.del(locMain     );
   TLocStruct& locPath     =locStruct[indexPath     ]; locStruct.del(locPath     );
   TLocStruct& locTemplate =locStruct[indexTemplate ]; locStruct.del(locTemplate );
   TLocStruct& locNamespace=locStruct[indexNamespace]; locStruct.del(locNamespace);
   TLocStruct& locTHIS     =locStruct[indexTHIS     ]; locStruct.del(locTHIS     );
   TLocStruct& locROOT     =locStruct[indexROOT     ]; locStruct.del(locROOT     );
   if (indexThis) 
   {
   TLocStruct& locThis     =locStruct[indexThis     ]; locStruct.del(locThis     );
   }
   if (indexNODE) 
   {
   TLocStruct& locNODE     =locStruct[indexNODE     ]; locStruct.del(locNODE     );
   }

   numLiter.clear(); intLiter.clear(); types.clear(); this_type_index=0;
   paramtypes.clear(); cases.clear(); gotos.clear(); debug.clear();
   lineToken=0; nesting=0; indexFunc=0; indexThis=0; indexNODE=0;
   dirTemplate=NULL;

   if (errCount) 
   {
   blocks.clear(); locVar.clear();
   stack.clear(); property.clear();
   locStruct.clear();
   gotoBackward.ward.clear(); gotoBackward.label.clear(); gotoForward.ward.clear(); gotoForward.label.clear();
   gotoLabel1  .ward.clear(); gotoLabel1  .label.clear(); gotoLabel2 .ward.clear(); gotoLabel2 .label.clear();
   trueChain   .ward.clear(); trueChain   .label.clear(); falseChain .ward.clear(); falseChain .label.clear();
   } 
   codes.clear(); 
   exerets.clear();
   property.clear();
#if defined(PROGRAM_MINIMUM_TYPE_FIELD)
   field_info_table.clear();
#endif

   //tree.clear(); 

   TOtParse::clear();
}

bool TOtTranslator::statements()
{

   exerets.push();
   blocks.push(TOtlBlock::blBlock);

   TREE_MARKER(0)  //  Program
   while (statement());
   TREE_LEAVE(trProgram)
   if (errCount) return false;
   if (nCompaund) { error(TString(lexMess_MissingBracket.system())+" }"); return false; }
   if (!blocks.pop()) return false;

   if (!exerets.isReturn() && typeOfResult().id!=id_void) {
      error(lexMess_WarningFuncNotReturn.system());
      }
   exerets.pop();

   return true;
}

bool TOtTranslator::statement(bool Switch)
{
   if (errMess && errMess->exit()) { error(lexMess_TaskCanceled.system()); return false; }
   if (exceeding()) return false;
   if (!(matchNo(TOtLexem::spRightCramp) || matchNo(TOtLexem::spSemiColon) ||
         matchNo(TOtLexem::rvCase)       || matchNo(TOtLexem::rvDefault)   ||
         matchNo(TOtLexem::lkResult)     ||
         eofLek()) && exerets.Unreachable()) {
      warning(lexMess_WarningUnreachable.system());
      }
   int lp=property.last();
   int bp=stack.indexOfTop();
   TOtLexem l;
   makeLine();
   if (eofLek()) {
      nesting--;
      return false;
      }
   else if (match(TOtLexem::spLeftCramp)) {
      if (!compound()) return false;
      }
   else if (match(TOtLexem::rvIf)) {
      if (! stIf() ) return false;
      }
   else if (match(TOtLexem::rvWhile)) {
      if (! stWhile() ) return false;
      }
   else if (match(TOtLexem::rvDo)) {
      if (! stDo() ) return false;
      }
   else if (match(TOtLexem::rvContinue)) {
      if (! stContinue() ) return false;
      }
   else if (match(TOtLexem::rvBreak)) {
      if (! stBreak() ) return false;
      }
   else if (Switch && (matchNo (TOtLexem::rvCase) || matchNo (TOtLexem::rvDefault) || matchNo (TOtLexem::spRightCramp))) {
      nesting--;
      return true;
      }
   else if (match(TOtLexem::rvFor)) {
      if (! stFor() ) return false;
      }
   else if (match(TOtLexem::rvForeach)) {
      if (! stForeach() ) return false;
      }
   else if (match(TOtLexem::rvSwitch)) {
      if (! stSwitch() ) return false;
      }
   else if (match(TOtLexem::rvConst)) {
      if (! stConst() ) return false;
      }
   else if (match(TOtLexem::rvGoTo)) {
      if (! stGoTo() ) return false;
      }
   else if (match(TOtLexem::rvEnum)) {
      if (! stEnum() ) return false;
      }
   else if (match(TOtLexem::rvStruct)) {
      if (! stStruct(mdsdsMain,NULL) ) return false;
      }
   else if (match(l,TOtLexem::rvReturn)) {
      if (! stReturn(l) ) return false;
      }
   else if (match(TOtLexem::rvTry)) {
      if (! stTry() ) return false;
      }
   else if (match(TOtLexem::rvThrow)) {
      if (! stThrow() ) return false;
      }
   else if (match(TOtLexem::rvFork)) {
      if (! stFork() ) return false;
      }
   else if (match(TOtLexem::rvSemaphore)) {
      if (! stSemaphore() ) return false;
      }
   else if (match(TOtLexem::spSemiColon)) {
      TREE_PUSH(trStatement,xel)
      nesting--;
      return true;
      }
#if defined(USE_PLSQL)
   else if (match(TOtLexem::rvSql)) {\
      if (! stPLSQL()) return false;
      if (! match(TOtLexem::spSemiColon)) {
         error(lexMess_MissingSemi.system());
         return false;
         }
      }
#endif
   else {
      if (!stDefine(true,false)) {
         if (errCount) return false;
         TREE_MARKER(0) //  Expression
         if (! voidExpression() ) return false;
         TREE_LEAVE(trExpression)
         if (eofLek()) { error(lexMess_UnexpectedEof.system()); return false; }
         if (! match(TOtLexem::spSemiColon)) {
            int j=beforeCode(codes.last()+1);
            int beforetype=TOtProgram::TToken ::none;
            if (j) beforetype=codes(j).type;
            if (!(getLanguage() & lkYesGoTo) || (beforetype!=TOtProgram::TToken::stLabel)) {
               error(lexMess_MissingSemi.system()); return false;
               }
            }
         }
      }
   if (stack.indexOfTop() != bp) {
      error(lexMess_UndueObject.system()); return false;
      }
   property.trunc(lp);
   nesting--;
   return true;
}

bool TOtTranslator::statement_block(TOtlBlock::tBlock block)
{
   blocks.push(block);
   if (!statement()) { if (!errCount) error(TString(lexMess_UnexpectedEof.system())); return false; }
   return blocks.pop();
}

bool TOtTranslator::statement_compound(TOtlBlock::tBlock block)
{
   blocks.push(block);
   if (!needBracket(TOtLexem::spLeftCramp,'{') || !compound()) return false;
   return blocks.pop();
}

bool TOtTranslator::compound() // group of operators
{
   TREE_MARKER(xel)  //  Statements
   ++nCompaund;
   blocks.push(TOtlBlock::blBlock);
   while (!match(TOtLexem::spRightCramp)) if (eofLek() || !statement()) return false;
   if (!blocks.pop()) return false;
   --nCompaund;
   TREE_LEAVE(trStatements)
   return true;
}

bool TOtTranslator::stReturn(const TOtLexem& l)
{
   TREE_MARKER(l)  //  Return
   TOtType result(castable(typeOfResult()));
   if (result.id!=id_void) {
      int iBeg=codes.last();
      if (!notVoidExpression()) return false;
      if (!prefixExpressionOperator(iBeg)) return false;
      int dept=0,cast=0,weight=0;
      const TOtType &stack_0=stack[0];
      if (stack_0==TOtType__Null) {
         cast=castNULL(result);
         }
      else {
         if (!castable(stack_0,result,dept) && !castable(stack_0,result,cast,weight)) {
            error(lexMess_InvalidObjectType.system()+" "+TOtMetaInfo::name(castable(stack_0))); return false;
            }
         }
#if defined(PROGRAM_MINIMUM_TYPE_FIELD)
      minimum_type(result,codes.last());
#endif
      genReturnValue(cast);
      }
   else {
      TREE_PUSH_TYPE(trNone)
      }
   TREE_LEAVE(trReturn)
   int before=codes.last();
   if (!blocks.exit((result.id==id_void)?TOtlBlock::gtReturn:TOtlBlock::gtReturnValue)) {
      error(lexMess_Misplaced.system()); return false;
      }
   int after=codes.last();
   exerets.exec(TExeRet::xeReturn);
   genReturn(result.id,l,((after==before) || (result.id==id_void))?oper_None:restore_return);
   return needBracket(TOtLexem::spSemiColon,';');
}

bool TOtTranslator::stGoTo()
{
   TREE_MARKER(xel)  //  GoTo
   TOtLexem l;
   if (!getIdentWithError(l)) return false;
   TREE_LEAVE(trGoTo)
   TOtProgram::TToken t;
   t.type=TOtProgram::TToken::delVar;
   t.oper=1;
   t.id=0;
   codeAdd(t);
   int token=genGoTo();
   TGoTo go(getText(l),token,blocks.count,l);
   blocks.getLocal(go.local);
   gotos.add(go);
   return true;
}

bool TOtTranslator::stConst()
{
   TREE_PUSH(trConst,xel)
   return stDefine(true,true);
}

TOtTranslator::TDefineType TOtTranslator::getDefineType(int mode)
{
   TDefineType df=dfNone, gn_df=dfNone;
   TOtLexem l; int form=ooNone|ooNoError;
   bool yes=true;
   if (mode&gdtRestitution) OnRestitution(); 
   if (!(mode&gdtOneType) && match(TOtLexem::lkResult)) {
      df=dfFunction;
      }
   else if (!(mode&gdtOneType) && match(TOtLexem::lkDefine)) {
      df=dfBaseVariable;
      }
   else if (getIdent(l)) {
      TString name=getText(l);
      if (varIndex(name) == 0) {
         TOtType v=TOtMetaInfo::type(name);
         if (v.id==id_unknown) {
            TString title("LRPtr$"); form|=ooTemplate;
            size_t len_pref=title.len();
            title+=name;
            if (getPrecise(l,title,len_pref,v,form)) {
               if (form & ooPrecise) {
                  if (match(TOtLexem::spLeftScrape)) {
                     if (!match(TOtLexem::spRightScrape)) yes=false;
                     }
                  }
               }
            else {
               yes=false;
               }
            }
         else if (TOtMetaInfo::castable(v.id,id_TOtObject)) {
            if (v.isDocument()) {
               if (match(TOtLexem::opAnd)) {
                  }
               else if (match(TOtLexem::spLeftScrape)) {
                  if (!match(TOtLexem::spRightScrape)) yes=false;
                  }
               }
            else if (!(mode&gdtOneType) && generic(v.id)) {
               if (match(TOtLexem::cpLess)) {
                  gn_df=getDefineType(gdtOneType);
                  if ((gn_df==dfNone) || !match(TOtLexem::cpGreat)) yes=false;
                  }
               }
            }
#ifdef FLORA_POINTER_OF_VOID
         else if (v.id==id_void) {
            }
#endif
         else {
            yes=false;
            }
         if (!(mode&gdtOneType) && yes) {
            if (match(TOtLexem::opMulti)) {
               while (match(TOtLexem::opMulti));
               }
            else {
               yes=false;
               }
            }
         }
      else {
         yes=false;
         }
      }
   else {
      yes=false;
      }
   if (!(mode&gdtOneType)) {
      if (yes) {
         if (match(TOtLexem::spLeftBracket) && match(TOtLexem::opMulti) && match(TOtLexem::lkIdent) && match(TOtLexem::spRightBracket)) {
            df=dfFunctionPointer;
            }
         else if (match(TOtLexem::lkIdent)) {
            if (df==dfNone) { df=dfVariable; if (form&ooTemplate) df=(TDefineType)(df|dfTemplate); }
            while (yes && match(TOtLexem::spColonColon)) {
               df=dfNone;
               if (!match(TOtLexem::lkIdent)) yes=false;
               }
            }
         else {
            yes=false;
            }
         }
      if (yes) {
         if (match(TOtLexem::spLeftBracket)) {
            if (df!=dfFunctionPointer) df=dfFunction;
            }
         else {
            if (df==dfFunctionPointer) df=dfNone;
            }
         }
      if (yes) { df=(TDefineType)(df|(gn_df<<16)); }
      }
   else {
      if (yes) { df=dfVariable; if (form&ooTemplate) df=(TDefineType)(df|dfTemplate); }
      }
   if (mode&gdtRestitution) OffRestitution(); 
   return df;
}

TOtTranslator::TDefType::TDefType() 
   :yes_document(false),yes_precise(false),yes_set(false),a_oper(oper_assign),ref_origin(id_void),size(0),id(0),df(dfNone)  
{}

bool TOtTranslator::stDefType(TDefType &def)
{
   TDefineType &df=def.df; 
   TOtProgram::TToken &t=def.t;
   TOtType &v=def.v, &c=def.c;
   bool    &yes_document=def.yes_document, &yes_precise=def.yes_precise;
   sbyte   &a_oper=def.a_oper;
   short   &ref_origin=def.ref_origin;
   if      (match(TOtLexem::dfNum)) {
      TREE_PUSH(trIdent,xel)
      t.type=TOtProgram::TToken::newNum;
      c=id_TOtRNum; v=id_TOtLRNum;
      t.oper=oper_castNum;
      }
   else if (match(TOtLexem::dfDec)) {
      TREE_PUSH(trIdent,xel)
      t.type=TOtProgram::TToken::newNum;
      c=id_TOtRNum; v=id_TOtLRNum;
      a_oper=oper_assignDec; t.oper=oper_castDec;
      }
   else if (match(TOtLexem::dfLong)) {
      TREE_PUSH(trIdent,xel)
      t.type=TOtProgram::TToken::newInt;
      c=id_TOtRInt; v=id_TOtLRInt;
      a_oper=oper_assignLong; t.oper=oper_castLong;
      }
   else if (match(TOtLexem::dfShort)) {
      TREE_PUSH(trIdent,xel)
      t.type=TOtProgram::TToken::newInt;
      c=id_TOtRInt; v=id_TOtLRInt;
      a_oper=oper_assignShort; t.oper=oper_castShort;
      }
   else if (match(TOtLexem::dfInt)) {
      TREE_PUSH(trIdent,xel)
      t.type=TOtProgram::TToken::newInt;
      c=id_TOtRInt; v=id_TOtLRInt;
      t.oper=oper_castInt;
      }
   else if (match(TOtLexem::dfStr)) {
      TREE_PUSH(trIdent,xel)
      t.type=TOtProgram::TToken::newStr;
      c=id_TOtRStr; v=id_TOtLRStr;
      }
   else if (match(TOtLexem::dfPtr)) {
      TREE_PUSH(trIdent,xel)
      t.type=TOtProgram::TToken::newPtr;
      TString title="LRPtr";
      TOtLexem l; int form=ooNone; v=TOtType::LRPtr;
      if (!getObliqueOrigin(l,title,v,form)) return false;
      if (form & ooStruct) {
         if (form & ooPrecise) {
            yes_precise=true;
            v.id=id_TOtLRPtr; c=v; c.id=id_TOtRPtr;
            }
         else {
            c=v; c.origin=-v.origin;
            }
         }
      else {
         v.id=id_TOtLRPtr; c=v; c.id=id_TOtRPtr;
         if (v.isDocumentOblique()) {
            yes_document=true;
            ref_origin=v.origin;
            }
         }
      if (!(form & (ooStruct | ooPrecise | ooTemplate)) && matchNo(TOtLexem::lkOblique)) {
         if (!getArrayObliqueOrigin(l,v)) return false;
         c=v; c.origin=-v.origin;
         }
      }
   else {
      TOtLexem l; int form=ooNone;
      if (!getIdentWithError(l)) return false;
      t.type=TOtProgram::TToken::newPtr;
      v=TOtMetaInfo::type(getText(l));
      if (v.id==id_unknown) {
         TString title("LRPtr$"); form|=ooTemplate;
         size_t len_pref=title.len();
         title+=getText(l);
         if (!getPrecise(l,title,len_pref,v,form)) return false;
         if (form & ooPrecise) {
            v.id=id_TOtLRPtr; c=v; c.id=id_TOtRPtr;
            if (match(TOtLexem::spLeftScrape)) {
               if (!needBracket(TOtLexem::spRightScrape,']')) return false;
               v.origin=c.origin=id_TOtDocumentList;
               a_oper=oper_assignRefArray; t.oper=oper_castRefArray;
               }
            else {
               v.origin=c.origin=id_TOtDocumentNode;
               a_oper=oper_assignRefType; t.oper=oper_castRefType;
               }
            }
         else {
            c=v; c.origin=-v.origin;
            }
         }
      else if (TOtMetaInfo::castable(v.id,id_TOtObject)
#ifdef FLORA_POINTER_OF_VOID
         || (v.id==id_void)
#endif
         ) {
         v.id=id_TOtLRPtr; v.oblique=1; c=v; c.id=id_TOtRPtr;
         if (v.isDocument()) {
            if (match(TOtLexem::opAnd)) {
               v.origin=c.origin=id_TOtDocumentNode;
               a_oper=oper_assignRefNode; t.oper=oper_castRefNode;
               }
            else if (match(TOtLexem::spLeftScrape)) {
               if (!needBracket(TOtLexem::spRightScrape,']')) return false;
               v.origin=c.origin=id_TOtDocumentList;
               a_oper=oper_assignRefList; t.oper=oper_castRefList;
               }
            else {
               a_oper=oper_assign; t.oper=oper_None;
               }
            }
         else if (generic(v.origin)) {
            if (match(TOtLexem::cpLess)) {
               if (!getArrayObliqueOrigin(l,v,(TOtTranslator::TDefineType)(df>>16))) return false;
               c=v; c.origin=-v.origin;
               if (!needBracket(TOtLexem::cpGreat,'>')) return false;
               }
            }
         }
      else {
         error(lexMess_InvalidObjectType.system()+" "+TOtMetaInfo::name(castable(v)),l); return false;
         }
      if (!needBracket(TOtLexem::opMulti,'*')) return false;
      while (match(TOtLexem::opMulti)) v.oblique++;
      if (match(TOtLexem::opAnd)) v.id=id_TOtLRPtr;
      }
   return true;
}

bool TOtTranslator::stDefArr(TDefType &def,TOtLexem &l,CSTRREF name,int mode)
{
   TOtProgram::TToken &t=def.t;
   TOtType &v=def.v, &c=def.c;
   bool yes_precise=def.yes_precise;
   int &size=def.size;
   bool yesRange=size, yesConst=(mode&mdsdaConst), noSet=(mode&mdsdaNoSet);
   TArray_Int chains(1,0,-20);
   TOtType vMy(v),cMy(c);
   if (v.isStructure()) {
      vMy.id=_id_pointer_array;
      cMy.id=_id_pointer_array;
      }
   else {
      vMy.id=_id_local_array;
      cMy.id=_id_local_array;
      }
   TLocVar newV(name,vMy);
   newV.size=size;
   newV.lex=l;
   int id=locVar.push(newV);
   if (yes_precise) {
      TOtLexem l_s(l); l_s.group=TOtLexem::glStr; l_s.type=TOtLexem::lkStr;
      l_s.idx=addStrLiter(v.templateName);
      genPushStr(l_s); stack.pop();
      }
   t.id=size;
   codeAdd(t,l);

   if (!yesRange) {
      chains.add(codes.last());
      }
   if (endPos) setLastObject(-id);
   TOtLexem lek;
   if (noSet || match(lek,TOtLexem::opSet)) {
      locVar[id].state=TLocVar::svInitiald;
      if (!needBracket(TOtLexem::spLeftCramp,'{')) return false;
      TREE_MARKER(xel) //  List
      int index=0;
      do {
         int iBeg=codes.last();
         if (yesConst)
            locVar[id].type=vMy;
         genPushInt(TInt(++index),mdgpiNone);
         if (yesRange)
            genPushArr(-id,l);
         else
            chains.add(genPushArr(-id,l,true));
         if (yesConst)
            locVar[id].type=cMy;
         int iToken=codes.last();
         if (!notVoidExpression()) return false;
         if (!voidBinaryOperator(iBeg,noSet?"=":getText(lek),iToken,codes[iToken].pos)) {
            if (errCount) return false;
            errorInvalidOperator("=", lex, 0x03); return false;
            }
         if (!isSimple(iToken,codes.last())) { error(lexMess_InvalidExpression.system()); return false; }
         }
      while (match(TOtLexem::spComma));
      if (!needBracket(TOtLexem::spRightCramp,'}')) return false;
      TREE_LEAVE(trList)
      TREE_TRANSVECTION(trBinaryOper,lek,2)
      if (size && (index!=size) || !index) { errorName(lexMess_RangeError.system(),l); return false; }
      if (!yesRange) {
         int idx=addIntLiter(TInt(index));
         for (int i=chains.low();i<=chains.last();i++) {
            TOtProgram::TToken& token=codes[chains[i]];
            if (i!=chains.low()) {
               token.id=idx;
               token.type=TOtProgram::TToken::pushInt;
               }
            else {
               token.id=index;
               }
            }
         locVar[id].size=index;
         blocks.incSize(index);
         }
      }
   else {
      if (yesConst || !yesRange) {
         if (yesConst)
            errorName(lexMess_NotInitialized.system(),l);
         else
            errorName(lexMess_RangeError.system(),l);
         return false;
         }
      }
   def.id=id;
   return true;
}

bool TOtTranslator::stDefine(bool yesFunc,bool yesConst)  // Num,Int,Str,Ptr
{
   bool rou=false;
   TOtFuncProfile profile;
   TDefType def;
   def.df=getDefineType();
   TDefineType df=(TDefineType)(def.df&dfMaska); 
   if ((df==dfFunction) || (df==dfFunctionPointer)) {
      if (yesFunc) {
         if (stLocalFunc(profile,def.df)) {
            df=(TDefineType)(def.df&dfMaska);
            if (df!=dfFunctionPointer) return true;
            rou=true;
            }
         else {
            if (errCount) return false;
            }
         }
      else {
         error(lexMess_ErrorFuncDefine.system()); return false; 
         }
      }
   else if ((df==dfVariable) || (df==dfBaseVariable)) {
      }
   else {  // dfNone
      if (yesConst) { // const <int> ident=value;        
         errorName(lexMess_InvalidOperator.system(),lex);
         }
      return false;
      }

   TOtProgram::TToken &t=def.t;
   TOtType &v=def.v, &c=def.c;
   bool    &yes_document=def.yes_document, &yes_precise=def.yes_precise;
   sbyte   &a_oper=def.a_oper;
   short   &ref_origin=def.ref_origin;

   if (!rou) {
      if (!stDefType(def)) return false;
      TREE_MARKER(0)  // List
      }
   else {  // rou
      t.type=TOtProgram::TToken::newPtr;
      v=TOtType(id_TOtLRPtr,1,id_unknown);
      int idRou;
      TLocStruct& loc=locStruct.create(idRou,true);
      loc.isMain=true;
      loc.isRou=true;
      loc.isFunc=true;
      loc.profile=profile;
      loc.setType(TOtType(id_TOtAFunc));

      TProgramTable::TFuncPtr f;
      f.profile_.attach(new TOtFuncProfile(loc.profile));
      f.mode=f.fncRoutine;
      f.definition=addType(TOtType::unknown);
      loc.knil=addFunc(f);

      v.id=_id_structure;
      v.origin=idRou;
      c=v;
      c.origin=-idRou;
      }

   if ((blocks.level()==1) && (getLanguage() & lkNoGlobal)) {
      error(lexMess_NotGlobal.system()); return false;
      }
   do {
      TOtLexem l;
      TString  name;
      if (rou) {
         l=lex;
         name=profile.name();
         }
      else {
         if (yes_document) {
            if (match(TOtLexem::opAnd)) {
               v.origin=c.origin=id_TOtDocumentNode;
               a_oper=oper_assignRefNode; t.oper=oper_castRefNode;
               }
            else if (match(TOtLexem::spLeftScrape)) {
               if (!needBracket(TOtLexem::spRightScrape,']')) return false;
               v.origin=c.origin=id_TOtDocumentList;
               a_oper=oper_assignRefList; t.oper=oper_castRefList;
               }
            else {
               v.origin=c.origin=ref_origin;
               a_oper=oper_assign; t.oper=oper_None;
               }
            }
         if (yes_precise) {
            if (match(TOtLexem::spLeftScrape)) {
               if (!needBracket(TOtLexem::spRightScrape,']')) return false;
               v.origin=c.origin=id_TOtDocumentList;
               a_oper=oper_assignRefArray; t.oper=oper_castRefArray;
               }
            else {
               v.origin=c.origin=id_TOtDocumentNode;
               a_oper=oper_assignRefType; t.oper=oper_castRefType;
               }
            }
         if (!getIdentWithError(l)) return false;
         name=getText(l);
         }
      int id_var=varIndex(name);
      int error_warning = TOtTranslateMessage::tNone;
      if (id_var<0) {
         if (locVar.indexOfTop()+id_var<blocks.getLocal()) 
            error_warning = TOtTranslateMessage::tError;
         else
            error_warning = TOtTranslateMessage::tWarning;
         }
      else if (id_var>0) {
         error_warning = TOtTranslateMessage::tWarning;
         }
      else {
         if (constArr.findConst(name, NULL, 0x01)) {
            error_warning = TOtTranslateMessage::tWarning;
            }
         }
      if (error_warning != TOtTranslateMessage::tNone) {
         TString mess=name; mess << " - "; mess << lexMess_DoubleName.system();
         warning_error(mess,l,error_warning);
         if (error_warning == TOtTranslateMessage::tError) return false;
         }
      int size=1;
      addDebug(TOtlBlock::blDefine);
      if (!rou && match(TOtLexem::spLeftScrape)) {  //  Type a[]
         TREE_MARKER(xel) //  List
         if (!match(TOtLexem::spRightScrape)) {
            TInt range; int val;
            if (calcExpression(id_TOtRInt,val)!=id_TOtRInt) return false;
            range=intLiter.get(val);
            if (!needBracket(TOtLexem::spRightScrape,']')) return false;
            if (range <1 || range>localDimension) { errorName(lexMess_RangeError.system(),l); return false; }
            def.size=range.getInt();
            }
         else {
            def.size=0;
            }
         TREE_LEAVE(trList)
         TREE_TRANSVECTION(trItem,xel,2)
        
         if (!stDefArr(def,l,name,yesConst?mdsdaConst:mdsdaNone)) return false;
         continue;
         }
      TLocVar newV(name,v);
      newV.lex=l;
      int id=locVar.push(newV);
      if (yes_precise) {
         TOtLexem l_s(l); l_s.group=TOtLexem::glStr; l_s.type=TOtLexem::lkStr;
         l_s.idx=addStrLiter(v.templateName);
         genPushStr(l_s); stack.pop();
         }
      t.id=size;
      codeAdd(t,l);
      if (rou) {
         const TLocStruct& loc=locStruct[v.origin];
         int index=-locVar.getAddress(id);
         if (indexFunc) {
            index+=blocks.getSize(1);
            const TOtFuncProfile &profile_func=locStruct[indexFunc].profile;
            index+=profile_func.param.count();
            }
         else {
            index*=-1;    //  global
            }
         T_Array<TProgramTable::TFuncPtr ,TArray::aoMemShift>&   program_func=program->table.object().func;
         program_func[loc.knil].index=index;
         }
      if (endPos) setLastObject(-id);
      TOtLexem lek;
      if (match(lek,TOtLexem::opSet)) {
         int iBeg=beforeCode(codes.last()+1);
         codes[iBeg].oper=a_oper;
         genNone(TOtProgram::TToken::none);
         stack.push(v);
         locVar[id].state=TLocVar::svInitiald | TLocVar::svDefinite;
         if (yesConst)
            locVar[id].type=c;
         int iToken=codes.last();
         if (!notVoidExpression()) return false;

         if (yesConst && (v.oblique)) {
            if (stack[0].isStructure()) {
               int idPath=abs(stack[0].origin);
               const TLocStruct& loc=locStruct[idPath];

               if (loc.isConst) {
                  TOtType rType=castable(stack[0]);
                  TOtType lType=castable(v);
                  lType.id=rType.id=id_TOtRPtr;
                  if (!TOtMetaInfo::castable(rType,lType)) {
                     if (loc.obj) {
                        error(lexMess_ObjectTypesMismatch.system(),l);
                        return false;
                        }
                     else {
                        stack[0]=lType;
                        }
                     }
                  locVar[id].path=idPath;
                  }
               }
            }

         if (!voidBinaryOperator(iBeg,lek,iToken)) {
            if (errCount) return false;
            errorInvalidOperator("=", lek, 0x03); return false;
            }
         locVar[id].state&=~TLocVar::svDefinite;
         }
      else {
         if (yesConst) {
            errorName(lexMess_NotInitialized.system(),l);
            return false;
            }
         }
      }
   while (!rou && match(TOtLexem::spComma));
   if (!rou) {
      TREE_LEAVE(trList)
      }
   TREE_TRANSVECTION(trDefinition,0,1+(rou?0:1)+(yesConst?1:0))
   if (!needBracket(TOtLexem::spSemiColon,';')) return false;
   return true;
}

bool TOtTranslator::stParam(TOtType& type,TDefineType df)
{
   bool ret=true; 
   TOtLexem l;
   int form=ooNone;
   if (match(l,TOtLexem::lkResult)) {
      TString title(getText(l));
      type=TOtMetaInfo::type(title);
      TREE_PUSH(trIdent,l)
      bool yesLPtr=TOtMetaInfo::castable(type.id,id_TOtLPtr);
      if (TOtMetaInfo::castable(type.id,id_TOtRPtr) || yesLPtr) {
         if (!getObliqueOrigin(l,title,type,form)) return false;
         if (!getDocType(type,form,df)) return false;
         if (!(form & (ooStruct | ooPrecise | ooTemplate)) && matchNo(TOtLexem::lkOblique)) {
            if (!getArrayObliqueOrigin(l,type)) return false;
            }
         }
      TREE_TRANSVECTION(trType,0,type.oblique?(type.oblique+2):1)
      }
   else if (match(l,TOtLexem::lkDefine)) {
      if (l.math(TOtLexem::dfInt) || l.math(TOtLexem::dfShort) || l.math(TOtLexem::dfLong)) {
         type=match(TOtLexem::opAnd)?TOtType::LRInt:TOtType::RInt;
         }
      else if (l.math(TOtLexem::dfNum) || l.math(TOtLexem::dfDec)) {
         type=match(TOtLexem::opAnd)?TOtType::LRNum:TOtType::RNum;
         }
      else if (l.math(TOtLexem::dfStr)) {
         type=match(TOtLexem::opAnd)?TOtType::LRStr:TOtType::RStr;
         }
      else {
         ret=false;
         }
      }
   else if (match(l,TOtLexem::lkIdent)) {
      type=TOtMetaInfo::type(getText(l));
      if (type.id==id_unknown) {
         TString title("RPtr$");
         size_t len_pref=title.len(); form|=ooTemplate;
         title+=getText(l);
         if (!getPrecise(l,title,len_pref,type,form)) return false;
         }
      else if (TOtMetaInfo::castable(type.id,id_TOtObject)
#ifdef FLORA_POINTER_OF_VOID
         || (type.id==id_void)
#endif
         ) {
         type.id=id_TOtRPtr; type.oblique=1; 
         }
      else {
         ret=false;
         }
      if (ret && !getDocType(type,form,df)) return false;
      if (ret && match(TOtLexem::opMulti)) {
         while (match(TOtLexem::opMulti)) type.oblique++;
         if (match(TOtLexem::opAnd)) {
            if (form & ooTemplate) 
               type.origin=abs(type.origin);
            else
               type.id=id_TOtLRPtr;
            }
         }
      else {
         ret=false;
         }
      }
   else {
      ret=false;
      }
   if (!ret) {
      error(lexMess_UnknownObjectType.system());  return false;
      }
   return true;
}

bool TOtTranslator::stFunc(TOtFuncProfile& profile,TOtLexem &fName,TDefineType& df,T_Array<TDefIdent,TArray::aoMemShift> *names_param,TArrayStr *owner)
{
   makeLine();

   TREE_MARKER(0) //  Header
   TOtLexem l(lex);
   TOtType type;
   if (!stParam(type,df)) return false;
   profile.result(type);
   if (TOtMetaInfo::castableToL(type)) {
      error(lexMess_InvalidObjectType.system()+" "+TOtMetaInfo::name(castable(type)),l); return false;
      }
   bool rou=false;
   if (match(TOtLexem::spLeftBracket)) {
      TREE_MARKER(xel) //  List
      if (!needBracket(TOtLexem::opMulti,'*')) return false;
      l=xel;
      rou=true;
      df=(TDefineType)(((int)df&~dfMaska)|dfFunctionPointer);
      }
   if (!getIdentWithError(fName)) return false;
   if (owner) {
      owner->clear();
      while (match(TOtLexem::spColonColon)) {
         owner->add(getText(fName));
         if (!getIdentWithError(fName)) return false;
         }
      }
   profile.name(getText(fName));
   if (rou) {
      TREE_TRANSVECTION(trPrefixOper,l,1)
      TREE_LEAVE(trList)
      if ( !needBracket(TOtLexem::spRightBracket,')')) return false;
      }
   if (!needBracket(TOtLexem::spLeftBracket,'(')) return false;
   TREE_MARKER(xel) //  List
   if (names_param)  names_param->clear();

   TOtFuncProfile::TCollDefault &defaults=profile.defaults;

   if (!match(TOtLexem::spRightBracket)) {
      do {
         TOtType type_param;
         makeLine();
         TOtLexem lexName=lex;
         TREE_MARKER(0)  //  Param
         if (! stParam(type_param) ) return false;
         if (type_param ==id_void) { error(lexMess_InvalidObjectType.system()+" "+TOtMetaInfo::name(castable(type_param)),lexName); return false; }
         profile.param.add(type_param);
         if (getIdent(lexName)) {
            TREE_PUSH(trIdent,lexName)
            }
         else {
            lexName.group=TOtLexem::glNone; lexName.type=TOtLexem::lkNone;
            }
         if (names_param) {
            TDefIdent def;
            if (lexName.math(TOtLexem::lkIdent)) {
               def.name=getText(lexName);
               def.lex=lexName;
               }
            names_param->add(def);
            }

         bool yesError=false;
         if (match(TOtLexem::opSet)) {
            int z=1;
            TString sZ,n;
            bool local=false;
            TOtLexem cLex;
            if (match(TOtLexem::opAdd)) {
               sZ=getText(xel);
               }
            else if (match(TOtLexem::opSub)) {
               z=-1;
               sZ=getText(xel);
               }
            if (match(TOtLexem::lkIdent)) {
               local=true;
               n=getText(xel);
               while (match(TOtLexem::spColonColon)) {
                  if (!getIdentWithError(lexName)) return false;
                  n+=scopeSign+getText(lexName);
                  }
               int c_ret = constArr.findConst(n), c = c_ret & TOtConst::ctTypeMask;
               if (c && !(c_ret & TOtConst::ctDynamic)) {
                  getConstLexem(c,cLex);
                  n=sZ+n; cLex.inm*=z; cLex.num*=z;
                  }
               else {
                  cLex.group=TOtLexem::glNone;
                  }
               }

            TOtFuncProfile::TDefault def;
            type_param =castable(type_param);
            switch (type_param.id) {
               case id_TOtRNum :
               case id_TOtRInt : {
                  if (local) {
                     if (cLex.math(TOtLexem::lkInt)) {
                        def.title=n;
                        def.ium=cLex.inm; def.num=cLex.num;
                        }
                     else if (cLex.math(TOtLexem::lkNum) && type_param.isRNum()) {
                        def.title=n;
                        def.num=cLex.num;
                        }
                     else {
                        yesError=true;
                        }
                     }
                  else if ((sZ.len()==0) && match(TOtLexem::ctNULL)) {
                     def.title=getText(xel);
                     def.ium=NIL_INT; def.num=NIL_NUM;
                     }
                  else if (match(TOtLexem::lkInt)) {
                     def.title=sZ+getText(xel);
                     def.ium=xel.inm*z; def.num=xel.num*z;
                     }
                  else if (match(TOtLexem::lkNum) && type_param.isRNum()) {
                     def.title=sZ+getText(xel);
                     def.num=xel.num*z;
                     }
                  else
                     yesError=true;
                  } break;
               case id_TOtRStr : {
                  if (sZ.len()!=0) {
                     yesError=true;
                     }
                  else if (local) {
                     if (cLex.math(TOtLexem::lkStr)) {
                        def.title=n;
                        def.str=getText(cLex);
                        }
                     else {
                        yesError=true;
                        }
                     }
                  else if (match(TOtLexem::lkStr)) {
                     def.title << '\"' << def.str << '\"';
                     def.str=getText(xel);
                     }
                  else if (match(TOtLexem::ctNULL)) {
                     def.title=getText(xel);
                     def.str=NIL_STR;
                     }
                  else
                     yesError=true;
                  } break;
               case id_TOtRPtr : {
                  if (local || (sZ.len()!=0)) {
                     yesError=true;
                     }
                  else if (match(TOtLexem::lkPath)) {
                     def.title << '`' << def.str << '`';
                     def.str=getText(xel);
                     }
                  else if (match(TOtLexem::ctNULL)) {
                     def.title=getText(xel);
                     def.str=NIL_STR;
                     }
                  else
                     yesError=true;
                  } break;
               default :
                  yesError=true;
               }
            if (!yesError) { defaults.add(def); }
            }
         else {
            if (defaults.count()) yesError=true;
            }
         if (yesError) { error(lexMess_InvalidParameters.system()); return false; }
         TREE_LEAVE(trParam)
         }
      while ( match(TOtLexem::spComma) );

      if (!needBracket(TOtLexem::spRightBracket,')')) return false;
      }
   TREE_LEAVE(trList)
   TREE_LEAVE(trHeader)
   return true;
}

bool TOtTranslator::stEnum()
{
   TREE_MARKER(xel) //  Definition
   int index;
   TLocStruct& loc=locStruct.create(index,true);
   loc.isEnum=true;
   loc.isMain=true;
   TOtLexem l;
   bool local=false;
   if (getIdent(l)) {
      TREE_PUSH(trIdent,l)
      int id=locStruct.findEnum(getText(l),EMPTY_STR);
      if (id<0) {
         errorName(lexMess_DoubleName.system(),l);
         return false;
         }
      loc.setName(getText(l));
      local=true;
      }
   else {
      TREE_PUSH_TYPE(trNone)
      }
   if (!needBracket(TOtLexem::spLeftCramp,'{')) return false;
   int cur=0;
   TREE_MARKER(xel) //  List
   do {
      TREE_MARKER(0) //  Enum
      if (!getIdentWithError(l)) return false;
      int id;
      if (local)
         id=locStruct.findEnum(loc.getName(),getText(l));
      else
         id=locStruct.findEnum(EMPTY_STR,getText(l));
      if (id<0) {
         errorName(lexMess_DoubleName.system(),l);
         return false;
         }
      int index_;
      TLocStruct& loc_=locStruct.create(index_);
      loc_.setName(getText(l));
      locStruct.add(loc,index_);
      if (match(TOtLexem::opSet)) {
         TInt result; int val;
         if (calcExpression(id_TOtRInt,val)!=id_TOtRInt) return false;
         result=intLiter.get(val);
         cur=result.getInt();
         }
      else {
         TREE_PUSH_TYPE(trNone)
         }
      loc_.link=cur++;
      loc_.isEnum=true;
      TREE_LEAVE(trEnum)
      }
   while ( match(TOtLexem::spComma) );
   if (!needBracket(TOtLexem::spRightCramp,'}')) return false;
   TREE_LEAVE(trList)
   TREE_LEAVE(trDefinition)
   return true;
}

bool TOtTranslator::stStruct(int mode, TLocStruct *struc)
{
   bool child=false,properties=false,references=false,typed=false,main=mode&mdsdsMain,user=(mode&mdsdsUser);
   int index;
   TLocStruct& loc=locStruct.create(index,main);
   loc.isStruct=true;
   if (!main) { locStruct.add(*struc,index); }
   TOtLexem l;
   TOtLexem lName;
   TOtType type;
   bool assembly=false;
   if (main) {            //  isMain
      assembly=tree.assembly;
      tree.assembly=false;
      if (!getIdentWithError(lName)) return false;
      int id=locStruct.structIndex(getText(lName));
      if (id<0) {
         errorName(lexMess_DoubleName.system(),lName);
         return false;
         }
      loc.isMain=true;
      loc.setName(getText(lName));
      references=(match(TOtLexem::rvReferences));
      if (!needBracket(TOtLexem::spColon,':')) return false;
      if (!references) {
         references=(match(TOtLexem::rvReferences));
         }
      if (getPath(l)) {
         TOtObjectRedirector *re=NULL;
         loc.isReferenc=references;
         loc.isPath=true;
         loc.isOpen=false;
         loc.obj=findObject(getText(l),re);
         if (!loc.obj) {
            loc.obj=findObject(getText(l),TOtType(id_TOtObject));
            }
         if (loc.obj) {
            type=loc.obj->objectType();
            }
         if (type==id_unknown) {
            error(TString(lexMess_CantFindObject.system()) + " : " + getText(l),l);
            return false;
            }
         loc.isChild=TOtMetaInfo::castable(type.id,id_TOtNode);
         locStruct.open(loc,false);
         typed=true;
         }
      else if (match(TOtLexem::spLeftBracket)) {
         if (!getString(l)) {
            error(lexMess_NoStrType.system(),l);  return false;
            }
         TString file=getText(l);
         if (!needBracket(TOtLexem::spComma,',')) return false;
         if (!getString(l)) {
            error(lexMess_NoStrType.system(),l);  return false;
            }
         TString section=getText(l);
         if (!needBracket(TOtLexem::spRightBracket,')')) return false;
         loc.isReferenc=references;
         loc.isPath=true;
         loc.isOpen=false;
         loc.obj=TOtObject::load(file,section,soptDontLoadChilds);
         if (loc.obj) {
            type=loc.obj->objectType();
            }
         if (type==id_unknown) {
            error(TString(lexMess_CantFindObject.system()) + " : " + getText(l),l); return false;
            }
         loc.isChild=TOtMetaInfo::castable(type.id,id_TOtNode);
         locStruct.open(loc,false);
         typed=true;
         }
      }

   if (!main || !typed) {
      if (!getIdentWithError(l)) return false;
      if (references) {
         error(lexMess_InvalidReferences.system(),l); return false;
         }
      loc.isOpen=true;
      int idType=abs(locStruct.structIndex(getText(l)));
      if (idType) {
         int ref=idType;
         while (main && ref) {
            if (ref==index) { 
               error(lexMess_RecursingInheritance.system(),lName); return false;
               }
            const TOtType &type2=locStruct[ref].getType();
            ref=(type2.isStructure())?type2.origin:0;
         }
         type.id=_id_structure;
         type.origin=idType;
         loc.isChild=locStruct[idType].isChild;
         }
      else {
         TString title(getText(l));
         type=TOtMetaInfo::type(title);
         if ((type==id_unknown) || !TOtMetaInfo::castable(type.id,id_TOtObject)) {
            error(lexMess_UnknownObjectType.system(),l); return false;
            }
         loc.isChild=!user && TOtMetaInfo::castable(type.id,id_TOtNode);
         if (TOtMetaInfo::castable(type.id,id_TOtRPtr)) {
            TOtLexem l_OO; int form=ooNone;
            if (!getObliqueOrigin(l_OO,title,type,form)) return false;
            type=node?node->metaType(title):TOtMetaInfo::type(title);
            }
         }
      }
   loc.setType(type);

   if (match(TOtLexem::spLeftCramp)) {
      if (!match(TOtLexem::spRightCramp)) {
         do {
            makeLine();
            TOtLexem ofsChild=lex;
            if (match(TOtLexem::rvSubObject)) {
               if (!needBracket(TOtLexem::spColon,':')) return false;
               properties=false;
               child=false;
               continue;
               }
            if (match(TOtLexem::rvProperties)) {
               if (!needBracket(TOtLexem::spColon,':')) return false;
               child=false;
               properties=true;
               continue;
               }
            if (match(TOtLexem::rvChilds)) {
               if (!needBracket(TOtLexem::spColon,':')) return false;
               if (!castable(loc.getType(),TOtType::Dir)) {
                  error(lexMess_NoDir.system(),ofsChild); return false;
                  }
               child=true;
               properties=false;
               continue;
               }

            TDefineType df=getDefineType(), my_df=(TDefineType)(df&dfMaska);
            TOtFuncProfile profile;
            TOtLexem fName;
            T_Array<TDefIdent,TArray::aoMemShift> names_param(profile.param.low(),5,5);
            int index_;
            if (((my_df==dfFunction) || (my_df==dfFunctionPointer)) && stFunc(profile,fName,df,&names_param)) {
               if (!needBracket(TOtLexem::spSemiColon,';')) return false;
               if (my_df==dfFunctionPointer) warning_error(lexMess_NoObject.system(),fName);
               TArrayStr nam(names_param.low(),names_param.last(),5);
               for (int k=names_param.low();k<=names_param.last();k++) {
                  nam.add(names_param[k].name);
                  }
               int index_my;
               TLocStruct& myLoc=locStruct.create(index_my);
               myLoc.isStruct=true;
               myLoc.profile=profile;
               myLoc.setType(TOtType(id_TOtAFunc));
               myLoc.isFunc=true;
               myLoc.path=profile.str(&nam);
                /*
               TOtLexem path;
               if (getPath(path) || getString(path)) {
                  TOtNode *owner=program->getOwnerNode();
                  if (owner) {
                     TOtNode *node;
                     if (path.type==TOtLexem::lkPath)
                        node=OT_DOWNCAST(owner->find(getText(path)),TOtNode);
                     else
                        node=owner->findNode(getText(path),TOtType::Node,owner);
                     if (node) {
                        profile.param.insert(profile.param.low(),TOtType(id_TOtRPtr,1,loc.getType().origin));
                        myLoc.obj=node->findFuncInside(profile,TOtFuncDemand::ffmdSubobject | TOtFuncDemand::ffmdPublished);
                        }
                     }
                  if (myLoc.obj==NULL) {
                     error(lexMess_CantFindObject,path.system());
                     return false;
                     }
                  myLoc.isStatic=true;
                  myLoc.path=myLoc.obj->getRelName(owner);
                  }
               */
               locStruct.add(loc,index_my);
               index_=index_my;
               }
            else {
               if (errCount) return false;
               if (!stStruct(properties?mdsdsUser:mdsdsNone,&loc)) return false;
               index_=loc.getChild(loc.count());
               }

            TLocStruct& loc_=locStruct[index_];
            short tid=castable(loc_.getType()).id;
            if (child && !TOtMetaInfo::derivedOwnableAsChild(tid,castable(loc.getType()).id) ||
               !child && !TOtMetaInfo::derivedOwnableAsSubobject(tid,castable(loc.getType()).id) && !properties ||
               !child && properties&& !derivedOwnableAsUserProperty(tid,castable(loc.getType()).id)) {
               warning_error(lexMess_NoInsert.system(),ofsChild);
               }

            loc_.isProperty=properties || user;
            loc_.isChild=!user && child;
            }
         while (!match(TOtLexem::spRightCramp));
         }
      }

   if (!main) {
      loc.isRef=(match(TOtLexem::opAnd) &&
                ((TOtMetaInfo::castable(loc.getType(),id_TOtValue) ||
                  TOtMetaInfo::castable(loc.getType(),id_TOtObjectPtr))));
      TOtLexem l_Name,lSynonym;
      if (!getIdent(l_Name) && !getPath(l_Name)) {
         error(lexMess_NoIdent.system());
         return false;
         }
      if (!getIdent(lSynonym)) {
         lSynonym=l_Name;
         }
      if (locStruct.find(*struc,getText(lSynonym))) {
         errorName(lexMess_DoubleName.system(),lSynonym);
         return false;
         }
      loc.path=getText(l_Name);
      loc.setName(getText(lSynonym));
      }
   else {                               //  isMain
      locStruct.setOwner(loc);
      TOtLexem l_var;
      if (getIdent(l_var)) {
         int id=varIndex(getText(l_var));
         if (id<0 && locVar.indexOfTop()+id<blocks.getLocal()) {
            errorName(lexMess_DoubleName.system(),l_var); return false;
            }
         TOtProgram::TToken t;
         TOtType v;
         t.type=TOtProgram::TToken::newPtr;
         v=TOtType(_id_structure,1,index);
         TLocVar newV(getText(l_var),v);
         newV.lex=l_var;
         locVar.push(newV);
         t.id=1;
         codeAdd(t,l_var);
         }
      tree.assembly=assembly;
      }
   if (!needBracket(TOtLexem::spSemiColon,';')) return false;
   return true;
}

    struct TCaseItem {
       TInt varIant; 
       TStr varSant;
       int  iBeg, iEnd;
       int  type;
       int  compare(const TCaseItem &join) const;
       friend int operator == ( const TCaseItem& key1, const TCaseItem& key2 ) { return key1.compare(key2) == 0;}
       friend int operator <  ( const TCaseItem& key1, const TCaseItem& key2 ) { return key1.compare(key2) <  0;}
    };
    int TCaseItem::compare(const TCaseItem &join) const
    {
       return (type==id_TOtRInt) ? flora::compare(varIant,join.varIant) : flora::compare(varSant,join.varSant);
    }

    class TCaseArray : public T_SortArray<TCaseItem,TCaseItem,TArray::aoMemShift> {
       public:
       TCaseArray() : T_SortArray<TCaseItem,TCaseItem,TArray::aoMemShift>(1,10,-20) {}
    };

bool TOtTranslator::stSwitch()  // switch ...
{
   TREE_MARKER(xel) //  Switch
   gotoForward.push();
   blocks.push(TOtlBlock::blSwitch);

   TOtType v(id_unknown);
   TLocVar newV(EMPTY_STR,v);
   locVar.push(newV);

   TOtProgram::TToken t;
   t.type=TOtProgram::TToken::none;
   t.id=1;
   TOtLexem l=lex;
   codeAdd(t,l);
   t.id=-locVar.indexOfTop();
   int iBeg=codes.last();
   genPushVar(t.id,l);
   int iToken_var=codes.last();
   TCaseArray variants;
   int table=id_void;
   if (!needBracket(TOtLexem::spLeftBracket,'(') || !notVoidExpression() || !needBracket(TOtLexem::spRightBracket,')')) return false;
   if (!prefixExpressionOperator(iBeg)) return false;
   v=stack[0];
   if      (TOtMetaInfo::castable(v,TOtType::RNum)) {
      codes[iBeg].type=TOtProgram::TToken::newNum;
      v=id_TOtLRNum;
      }
   else if (TOtMetaInfo::castable(v,TOtType::RInt)) {
      codes[iBeg].type=TOtProgram::TToken::newInt;
      v=id_TOtLRInt;
      table=id_TOtRInt;
      }
   else if (TOtMetaInfo::castable(v,TOtType::RStr)) {
      codes[iBeg].type=TOtProgram::TToken::newStr;
      v=id_TOtLRStr;
      table=id_TOtRStr;
      }
   else if (TOtMetaInfo::castable(v.id,id_TOtRPtr)) {
      codes[iBeg].type=TOtProgram::TToken::newPtr;
      v.id=id_TOtLRPtr;
      }
   else {
      error(lexMess_InvalidExpression.system());  return false;
      }
   locVar[0].type=v;
   stack[-1]=v;
   if (!voidBinaryOperator(iBeg,"=",iToken_var,codes[iToken_var].pos)) {
      error(lexMess_InvalidExpression.system());  return false;
      }
   if (!needBracket(TOtLexem::spLeftCramp,'{')) return false;
   int iSet=beforeCode(codes.last()+1);
   TREE_MARKER(xel)
   exerets.push();
   if (!matchNo(TOtLexem::rvCase) && !matchNo(TOtLexem::rvDefault) && !matchNo(TOtLexem::spRightCramp)) {
      error(TString(lexMess_MissingBracket.system())+" case"); return false;
      }
   int nCase=0;
   bool yesCase=true;
   TCaseItem item; item.type=table;
   while (yesCase) {
      TREE_MARKER(xel)  //  Case
      TREE_MARKER(lex)  //  List
      while (match(TOtLexem::rvCase)) {
         if (nCase) {
            saveLine();
            gotoLabel1.push();
            gotoLabel1.add(genGoTo());
            gotoLabel2.popLabel();
            restoreLine();
            }
         item.iBeg=codes.last();
         if (codes[item.iBeg].type == TOtProgram::TToken::line) item.iBeg--;
         l=lex;
         genPushVar(t.id,l);
         int iToken=codes.last();
         int intCalc=id_void;
         if (item.type) {
            int val;
            intCalc=calcExpression(item.type,val,0x04); // id_unknown - !calc, id_void - error, <id_NULL,id_TOtRNum,id_TOtRInt,id_TOtRStr>
            if (intCalc==id_void) return false;
            if (intCalc==id_NULL) {
               if (item.type==id_TOtRInt) item.varIant=TInt::nullVal; else item.varSant=TStr::nullVal;
               intCalc=item.type;
               }
            else if (intCalc==item.type) {
               if (item.type==id_TOtRInt) item.varIant=intLiter.get(val); else item.varSant=strLiter.get(val);
               }
            else
               table=id_void;
            }
         else {
            if (!notVoidExpression() || !prefixExpressionOperator(iToken)) return false;
            }
         if (!needBracket(TOtLexem::spColon,':')) return false;
         if (!binaryOperator(iBeg,"==",iToken,codes[iToken].pos)) return false;
         gotoLabel2.push();
         int iCase=genIf(-1);
         if (!iCase) return false;
         if (item.type && (item.type==intCalc)) {
            int k;
            if (variants.findKey(&item,k)) { error(TString(lexMess_DoubleValue.system())); return false; }
            item.iEnd=codes.last();
            variants.add(item);
            }
         gotoLabel2.add(iCase);
         if (nCase) {
            gotoLabel1.popLabel();
            }
         nCase++;
         }
      TREE_LEAVE(trList)
      blocks.push(TOtlBlock::blCase);
      TREE_MARKER(0) //  List
      do {
         if (!statement(true)) {
            if (!errCount) error(TString(lexMess_UnexpectedEof.system())); return false;
            }
         }
      while (!matchNo(TOtLexem::rvCase) && !matchNo(TOtLexem::rvDefault) && !matchNo(TOtLexem::spRightCramp));
      TREE_LEAVE(trList)
      if (!blocks.pop()) return false;
      exerets.exec(TExeRet::xeCase);
      if (!matchNo(TOtLexem::rvCase)) {
         yesCase=false;
         }
      TREE_LEAVE(trCase)
      }
   if (nCase) {
      gotoLabel2.popLabel();
      }
   int iDefault=codes.last();
   if (codes[iDefault].type != TOtProgram::TToken::line) iDefault++;
   int xe=TExeRet::xeNone;
   if (match(TOtLexem::rvDefault)) {
      TREE_MARKER(xel) //  Default
      if (!needBracket(TOtLexem::spColon,':')) return false;
      blocks.push(TOtlBlock::blCase);
      TREE_MARKER(0) //  List
      do {
         if (!statement(true)) {
            if (!errCount) error(TString(lexMess_UnexpectedEof.system())); return false;
            }
         }
      while (!matchNo(TOtLexem::rvCase) && !matchNo(TOtLexem::rvDefault) && !matchNo(TOtLexem::spRightCramp));
      TREE_LEAVE(trList)
      exerets.exec(TExeRet::xeEnd);
      xe=TExeRet::xeContinue | TExeRet::xeReturn;
      blocks.pop();
      TREE_LEAVE(trDefault)
      }
   if (!needBracket(TOtLexem::spRightCramp,'}')) return false;

   if (table) {
      codes[iBeg+1].type=TOtProgram::TToken::none;

      TOtProgram::TCase case_item;
      case_item.token=iDefault;
      case_item.count=0;
      cases.add(case_item);
      int index=cases.last();
      codes[iSet].type=TOtProgram::TToken::stSwitch;
      codes[iSet].id=index;

      for (int i=variants.low();i<=variants.last();i++) {
         TCaseItem &variant=variants[i];
         int variant_body = variant.iEnd + 1;
         for (int j=variant.iBeg+1;j<=variant.iEnd;j++) {
            if (codes[j].type != TOtProgram::TToken::line) {
               codes[j].type = TOtProgram::TToken::none;
               }
            else {
               variant_body = j;
               }
            }
         TOtProgram::TCase case_item2;
         case_item2.token=variant_body;
         case_item2.variant=(table==id_TOtRInt) ? addIntLiter(variant.varIant) : addStrLiter(variant.varSant);
         cases.add(case_item2);
         cases[index].count++;
         }
      if (table==id_TOtRStr) {
         cases[index].count*=-1;
         }
      }
   TREE_LEAVE(trList)
   exerets.pop(xe,true);
   if (!blocks.pop()) return false;
   gotoForward.popLabel();
   TREE_LEAVE(trSwitch)
   return true;
}

bool TOtTranslator::stThen_Else()  // if ... else
{
   exerets.push();

   if (!statement_block(TOtlBlock::blBlock)) return false;

   exerets.exec(TExeRet::xeEnd);
   exerets.exec(TExeRet::xeBeg);
   if ( match(TOtLexem::rvElse) ) {
      saveLine();
      gotoLabel1.push();
      gotoLabel1.add(genGoTo());
      falseChain.popLabel();
      restoreLine();

      if (!statement_block(TOtlBlock::blBlock)) return false;

      gotoLabel1.popLabel();
      exerets.exec(TExeRet::xeEnd);
      exerets.pop(TExeRet::xeBreak|TExeRet::xeContinue|TExeRet::xeReturn|TExeRet::xeBreakCase);
      }
   else {
      falseChain.popLabel();
      exerets.pop(TExeRet::xeBreakCase);
      }
   return true;
}

bool TOtTranslator::stIf()  // if ... else
{
   TREE_MARKER(xel)  //  If
   trueChain.push();falseChain.push();

   if (!needBracket(TOtLexem::spLeftBracket,'(') || !jumpExpression(false) || !needBracket(TOtLexem::spRightBracket,')')) return false;
   if (!stThen_Else()) return false;

   TREE_LEAVE(trIf)
   return true;
}

bool TOtTranslator::stContinue()  //  ...  continue ...
{
  TREE_PUSH(trContinue,xel)
  if (!blocks.exit(TOtlBlock::gtContinue)) {
     error(lexMess_Misplaced.system()); return false;
     }
  exerets.exec(TExeRet::xeContinue);
  gotoBackward.add(genGoTo());
  return needBracket(TOtLexem::spSemiColon,';');
}

bool TOtTranslator::stBreak()  //  ...  break ...
{
  TREE_PUSH(trBreak,xel)
  if (!blocks.exit(TOtlBlock::gtBreak)) {
     error(lexMess_Misplaced.system()); return false;
     }
  exerets.exec(TExeRet::xeBreak);
  gotoForward.add(genGoTo());
  return needBracket(TOtLexem::spSemiColon,';');
}

bool TOtTranslator::stLocalFunc(TOtFuncProfile &profile,TDefineType& df)
{
   TArrayStr owner(1,3,3);
   T_Array<TDefIdent,TArray::aoMemShift> names_param(profile.param.low(),5,5);
   TOtLexem fName;
   bool rou;
   if (blocks.level()==1) {
      if (!stFunc(profile,fName,df,&names_param,&owner)) return false;
      rou=((df&dfMaska)==dfFunctionPointer);
      }
   else {
      if (!stFunc(profile,fName,df,&names_param,NULL)) return false;
      rou=((df&dfMaska)==dfFunctionPointer);
      if (!rou) { error(lexMess_ErrorFuncDefine.system()+" "+profile.name()); return false; }
      }
   if (rou) {
      TREE_TRANSVECTION(trFunction,0,1)
      return true;
      }
//   if (profile.defaults.count()) { error(lexMess_ErrorFuncDefine.system()+" "+profile.name); return false; }
   TString str=locStruct.str(profile);
   int idOwner=indexMain,idError=owner.low();
   if (owner.count()) {
      idOwner=abs(locStruct.structIndex(owner[idError]));
      }
   for (int i=idError+1;idOwner && i<=owner.count();i++) {
      idOwner=locStruct.find(idOwner,owner[i]);
      idError=i;
      }
   if (!idOwner) { error(lexMess_UnknownIdentify.system()+" "+owner[idError]); return false; }
   int indexHeader=0;
   const TLocStruct& loc=locStruct[idOwner];
   for (int i=1;i<=loc.count();i++) {
      const TLocStruct& f=locStruct[loc.getChild(i)];
      if (f.isFunc && (locStruct.str(f.profile)==str)) {
         indexHeader=loc.getChild(i);
         break;
         }
      }
   if (owner.count() && !indexHeader) {
      error(lexMess_UnknownIdentify.system()+" "+profile.name()); return false;
      }
   int myIndex;
   TLocStruct& myLoc=locStruct.create(myIndex);
   myLoc.profile=profile;
   myLoc.setType(TOtType(id_TOtAFunc));
   myLoc.isFunc=true;
   if (match(TOtLexem::spSemiColon)) {      // void f();
      if (indexHeader) {
         locStruct.del(myLoc);
         error(lexMess_DoubleName.system());
         }
      else {
         locStruct.add(locStruct[indexMain],myIndex);
         }
      TREE_TRANSVECTION(trFunction,0,1)
      }
   else if (match(TOtLexem::spLeftCramp)) { // void f() {}
      TREE_MARKER(xel)  //  Statements
      if (indexHeader) {
         locStruct.del(myLoc);
         if (locStruct[indexHeader].func) {
            error(lexMess_DoubleBody.system());
            return false;
            }
         else {
            indexFunc=indexHeader;
            }
         }
      else {
         indexFunc=myIndex;
         locStruct.add(locStruct[indexMain],myIndex);
         }
//      saveLine();
      gotoLabel1.push();
      gotoLabel1.add(genGoTo(fName)); // goto + debbuger
      exerets.Unreachable();
      exerets.push();
      blocks.push(TOtlBlock::blFunction);
      locStruct[indexFunc].func=genEntry(profile.param.count(),fName);
//      restoreLine();
      for ( int i=profile.param.low();i<=profile.param.last();i++) {
         TLocVar newV(names_param[i].name,profile.param[i]);
         newV.lex=names_param[i].lex;
         locVar.push(newV);
         }
      ++nCompaund;
      blocks.push(TOtlBlock::blBlock);
      while (!match(TOtLexem::spRightCramp)) if (eofLek() || !statement()) return false;
      if (!blocks.pop()) return false;
      --nCompaund;
      if (!exerets.isReturn()) {
         if (typeOfResult().id!=id_void) { error(lexMess_WarningFuncNotReturn.system()); return false; }
         genReturn(typeOfResult().id,lex);
         }
      if (!blocks.pop()) return false;
      indexFunc=0;
      exerets.pop(TExeRet::xeNone);
      gotoLabel1.popLabel();
      TREE_LEAVE(trStatements)
      TREE_TRANSVECTION(trFunction,0,2)
      }
   else {
      error(TString(lexMess_MissingBracket.system())+" {"); return false;
      }
   return true;
}

bool TOtTranslator::stWhile()  // while ...
{
  TREE_MARKER(xel)  //  While
  gotoBackward.push();
  gotoForward.push();
  trueChain.push();falseChain.push();
  if (!needBracket(TOtLexem::spLeftBracket,'(') || !jumpExpression(false) || !needBracket(TOtLexem::spRightBracket,')')) return false;
  gotoForward.merge(falseChain);

  exerets.push();
  if (!statement_block(TOtlBlock::blWhile)) return false;
  exerets.pop(TExeRet::xeNone);

  saveLine();
  gotoBackward.add(genGoTo());
  gotoBackward.pop();
  gotoForward.popLabel();
  restoreLine();
  TREE_LEAVE(trWhile)
  return true;
}

bool TOtTranslator::stDo()  // do ... while
{
  TREE_MARKER(xel) //  Do
  gotoBackward.push();
  gotoForward.push();
  trueChain.push();falseChain.push();

  exerets.push();
  if (!statement_block(TOtlBlock::blDo)) return false;
  exerets.pop(TExeRet::xeReturn);

  gotoBackward.setLabel();
  if (!match(TOtLexem::rvWhile)) { error(lexMess_MissingWhile.system()); return false; }
  if (!needBracket(TOtLexem::spLeftBracket,'(') ||
      !jumpExpression(true)                     ||
      !needBracket(TOtLexem::spRightBracket,')') ||
      !needBracket(TOtLexem::spSemiColon,';')   ) return false;
  trueChain.pop();
  gotoBackward.pop();
  gotoForward.popLabel();
  TREE_LEAVE(trDo)
  return true;
}

bool TOtTranslator::stFor()  // for (st1;Ex;st2) st3
{
   TREE_MARKER(xel)  //  For
   if (!needBracket(TOtLexem::spLeftBracket,'(')) return false;
   gotoForward.push();                             //        break => iEnd
   blocks.push(TOtlBlock::blFor);
   if (! stDefine(false,false)) {
      if (errCount) return false;
      if (!match(TOtLexem::spSemiColon)) {
         TREE_MARKER(0)
         do {                                      //        st1
            if (! voidExpression() ) return false;
            }
         while ( match(TOtLexem::spComma) );
         if (!needBracket(TOtLexem::spSemiColon,';')) return false;
         TREE_LEAVE(trList)
         }
      else {
         TREE_PUSH_TYPE(trNone)
         }
      }
   gotoLabel1.push();
   gotoLabel2.push();
   falseChain.push();
   if (!match(TOtLexem::spSemiColon)) {
      trueChain.push();
      if (!jumpExpression(false)) return false;    // iEx:   Ex
      if (!needBracket(TOtLexem::spSemiColon,';')) return false;
      }
   else {
      TREE_PUSH_TYPE(trNone)
      }
   gotoLabel2.add(genGoTo());                      //        goto => iSt3
   gotoBackward.push();                            //        continue => iSt2
   if (!match(TOtLexem::spRightBracket)) {
      TREE_MARKER(0)
      blocks.push(TOtlBlock::blBlock);
      do {                                         // iSt2:  st2
         if (! voidExpression() ) return false;
         }
      while ( match(TOtLexem::spComma) );
      if (!needBracket(TOtLexem::spRightBracket,')')) return false;
      if (!blocks.pop()) return false;
      TREE_LEAVE(trList)
      }
   else {
      TREE_PUSH_TYPE(trNone)
      }
   saveLine();
   gotoLabel1.add(genGoTo());                      //        goto => iEx
   gotoLabel1.pop();
   gotoLabel2.popLabel();
   restoreLine();

   exerets.push();
   if (!statement_block(TOtlBlock::blBlock)) return false;  // iSt3:  st3
   exerets.pop(TExeRet::xeNone);

   saveLine();
   gotoBackward.add(genGoTo());                    //        goto => iSt2
   gotoBackward.pop();
   falseChain.popLabel();
   if (!blocks.pop()) return false;
   gotoForward.popLabel();
   restoreLine();
   TREE_LEAVE(trFor)
   return true;
}

struct TRecForeach {
public:
   TRecForeach() :var(0), prop(0), arr(0), loc(0) {}
public:
   TString title;
   TOtType type;
   TString field;
   TOtLexem lex_title, lex_field;
   int var, prop, arr, loc;
   TOtTranslator::TDefType def;
   };
class TRecForeachArray : public T_BoundedArray<TRecForeach,1,10,-20,TArray::aoMemShift> {
public:
   int findField(CSTRREF);
   };
int TRecForeachArray::findField(CSTRREF name)
{
   for (int i=low();i<=last();i++) {
      const TRecForeach& item=(*this)[i];
      if (item.field==name) return i;
      }
   return 0;
}

bool TOtTranslator::stForeach()  // foreach (def[,def];Ex[,[--][index]][;[ItemCount] count]) st
{
//   program->setOptimize(0);
   TREE_MARKER(xel)  //  Foreach
   if (!needBracket(TOtLexem::spLeftBracket,'(')) return false;
   blocks.push(TOtlBlock::blForeach);

   TRecForeachArray items;
   TOtLexem lex_foreach(xel), lex_object(lex_foreach);
   if ( !match(TOtLexem::spSemiColon) ) {
      do {
         TRecForeach item;
         item.def.df=getDefineType();
         TDefineType df=(TDefineType)(item.def.df&dfMaska);
         if ((df==dfVariable) || (df==dfBaseVariable)) {
            item.lex_title=lex;
            if (!stDefType(item.def)) return false;
            }
         else {
            if (!getIdentWithError(item.lex_title)) return false;
            item.title=getText(item.lex_title);
            }
         if (getIdent(item.lex_field)) {
            item.field=getText(item.lex_field);
            }
         else {
            item.field=item.title; item.lex_field=item.lex_title;
            }
         if (items.findField(item.field)) {
            errorName(lexMess_DoubleName.system(),item.lex_field);
            return false;
            }
         items.add(item);
         }
      while ( match(TOtLexem::spComma) );
      if (!needBracket(TOtLexem::spSemiColon,';')) return false;
      }

   enum TMode { mdUnknown, mdCursor, md_Count=0x0010, mdObject, mdRec, mdLocal, mdIn, mdBits, 
      mdString  =0x0040, mdStringLine =mdString + md_Count+1, mdStringChar, mdStringNext=mdString + 3, 
      mdUserProp=0x0020, mdObjUserProp=mdUserProp+md_Count+1, mdObjUser_Prop, mdUserPropItem, mdUserPropField, mdUser_PropField 
   } mode=mdUnknown;
   TOtType type_object;
   TOtProgram::TToken t;
   int size=1;

   int id_object=0, loc_object=0; // LocalArray, Rec, Cursor
   TOtProgram::TUserProperty u_prop; // UserProp
   int id_u_prop=0;
   int prop_first=0, prop_last=0, func_first=0, func_last=0, func_move=0, result_move=id_void; // Cursor
   int func_item=0; // String
   OnRestitution(); 
   if (getIdent(lex_object) && (match(TOtLexem::spComma) || match(TOtLexem::spSemiColon) || match(TOtLexem::spRightBracket))) {
      if ((id_object=-varIndex(getText(lex_object))) > 0) {
         type_object=locVar[id_object].type;
         if (type_object.id==_id_local_array || type_object.id==_id_pointer_array) {
            mode=mdLocal;
            }
         }
      }
   OffRestitution(); 

   if (matchNo(TOtLexem::spLeftCramp)) {
      if (items.count()!=1) { error(lexMess_BadCountParameters.system(),lex_foreach); return false; }
      TRecForeach& first=items[items.low()];
      if (!stDefArr(first.def,lex,EMPTY_STR,mdsdaNoSet)) return false;
      id_object=first.def.id;
      type_object=locVar[id_object].type;
      mode=mdIn;
      }
   else if (mode==mdLocal) {
      match(TOtLexem::lkIdent);
      }
   else {
      type_object=TOtType::LRPtrObject;
      // object
      TLocVar var_object(EMPTY_STR,type_object); var_object.lex=lex_object;
      id_object=locVar.push(var_object);
      t.type=TOtProgram::TToken::newPtr; t.id=size; t.oper=oper_assign;
      codeAdd(t,lex_foreach);
   
      int token_new_object=beforeCode(codes.last()+1);
      genNone(TOtProgram::TToken::none);
      stack.push(type_object); // TOtType::LRPtrObject
      locVar[id_object].state=TLocVar::svInitiald;
      int iToken=codes.last();
   
      if (! notVoidExpression() ) return false;
      type_object=stack[0];
      if ((type_object.id==_id_property) && (type_object.oblique==1)) {
         bool potentially_user_prop=(type_object.origin < 0);
         const TProperty &prop=property[abs(type_object.origin)];
         type_object=prop.result();
         if (prop.user && potentially_user_prop) {
            if (items.empty()) { error(lexMess_BadCountParameters.system(),lex_foreach); return false; }
            TRecForeach& first=items[items.low()];
            id_u_prop=prop.fget;
            TOtProgram::TUserProperty& u=program->props[id_u_prop]; u_prop=u; 
            if ((u.prop.type==TUserData::ptArrRec) && (u.field.type==TUserData::ptNone)){
               if (type_object.isStructureOblique() && locStruct[abs(type_object.origin)].obj) 
                  mode=mdUserPropField;
               else
                  mode=mdUser_PropField;
               }
            if ((u.prop.type>=TUserData::ptArrNum) && (u.prop.type<=TUserData::ptArrPtr) ||
                (u.prop.type==TUserData::ptArrRec) && (u.field.type>=TUserData::ptNum) && (u.field.type<=TUserData::ptPtr)){
               if (items.count() > 1) {
                  error(lexMess_UndueObject.system(),items[items.low()+1].lex_title); return false;
                  }
               first.type=prop.c.result;
               mode=mdUserPropItem;
               }
            stack[0]=type_object;
            if (u.field.index) {
               TOtProgram::TToken& token=codes[u.field.index]; token.type=token.none;
               u.field.index=0;
               }
            if (u.prop.index) {
               TOtProgram::TToken& token=codes[u.prop .index]; token.type=token.none;
               u.prop.index=0;
               }
            }
         }
      if ((mode==mdUnknown) && castable(type_object,TOtType(id_TOtRPtr,1,id_TDbADataCursor))) {
         if (items.empty()) {
            mode=mdCursor;
            }
         }
      if ((mode==mdUnknown) && !items.empty() && type_object.isStructureOblique()) {
         const TRecForeach& first=items[items.low()];
         int owner=abs(type_object.origin);
         loc_object=owner;
         const TLocStruct& loc=locStruct[owner];
         if (loc.obj) {
            int prop=loc.obj->findUserProp(first.title);
            if (prop) {
               mode=mdObjUserProp;
               }
            }
         int field=(mode==mdUnknown)?locStruct.find(owner,first.title):0;
         if (field) {
            const TLocStruct& loc2=locStruct[field];
            if (loc2.isProperty) {
               mode=mdObjUser_Prop;
               }
            else if (castable(loc2.getType(), TOtType(id_TOtRec)) && castable(type_object,TOtType(id_TOtRPtr,1,id_TOtObjectArrRec))) {
               mode=mdRec;
               }
            else if (castable(loc2.getType(), TOtType(id_TDbField)) && castable(type_object,TOtType(id_TOtRPtr,1,id_TDbADataCursor))) {
               mode=mdCursor;
               }
            }
         if (loc.isXML) {
            }
         }

      if ((mode==mdUnknown) && castable(type_object, TOtType::RPtrObject)) {
         mode=mdObject;
         }
      if ((mode==mdUnknown) && castable(type_object, TOtType::RStr)) {
         if (items.count() != 1) { error(lexMess_BadCountParameters.system(),lex_foreach); return false; }
         const TRecForeach& first=items[items.low()];
         if (first.def.v.id==id_TOtLRStr) {
            mode=mdStringLine;
            }
         else if (first.def.v.id==id_TOtLRInt) {
            mode=mdStringChar;
            }
         else {
            error(lexMess_InvalidObjectType.system(),first.lex_title); return false;
            }
         stack[-1]=id_TOtLRStr;
         codes[token_new_object].type=TOtProgram::TToken::newStr;
         }
      if ((mode==mdUnknown) && castable(type_object, TOtType::RInt)) {
         if (items.count() > 1) { error(lexMess_BadCountParameters.system(),lex_foreach); return false; }
         if (!items.count()) {
            TRecForeach item;
            item.def.v.id=id_TOtLRInt;
            mode=mdBits;
            items.add(item);
            }
         else {
            const TRecForeach& first=items[items.low()];
            if (first.def.v.id==id_TOtLRInt) {
               mode=mdBits;
               }
            else {
               error(lexMess_InvalidObjectType.system(),first.lex_title); return false;
               }
            }
         stack[-1]=id_TOtLRInt;
         codes[token_new_object].type=TOtProgram::TToken::newInt;
         }
      if (mode==mdUnknown) { error(lexMess_InvalidObjectType.system(),lex_foreach); return false; }
      locVar[id_object].type=type_object;
   
      if (!voidBinaryOperator(token_new_object,"=",iToken,lex.ofsMain())) {
         if (errCount) return false;
         errorInvalidOperator("=", lex_foreach, 0x03); return false;
         }
      }
   if (items.empty() && (mode!=mdCursor) && (mode!=mdBits)) { error(lexMess_BadCountParameters.system(),lex_foreach); return false; }

   TOtLexem  lex_type_count(lex_foreach),  lex_count(lex_foreach),  lex_index(lex_foreach);
   TString  name_type_count, name_count, name_index;
   int prop_count=0;
   int way=0;
   bool yes_index=false, yes_name_type_count=false;
   if ( match(TOtLexem::spComma) ) {
      if ( !way && match(TOtLexem::opAddAdd) ) way=+1;
      if ( !way && match(TOtLexem::opSubSub) ) way=-1;
      if ( getIdent(lex_index) ) {
         name_index=getText(lex_index); yes_index=true;
         if (items.findField(name_index)) { errorName(lexMess_DoubleName.system(),lex_index); return false; }
         }
      if ( !way && match(TOtLexem::opAddAdd) ) way=+1;
      if ( !way && match(TOtLexem::opSubSub) ) way=-1;
      }
   if ( !way ) way=+1;

   // count(define)
   int id_count=0; // mdStringNext(id_pos)
   TInt count_value; bool count_calc = false;
   if ((mode==mdBits) || (mode==mdLocal) || (mode==mdIn)) { // + code(var)
      TLocVar var_count(name_count,TOtType::LRInt); var_count.state=TLocVar::svInitiald;
      id_count=locVar.push(var_count);
      int token_bit_count=codes.last();
      t.type=TOtProgram::TToken::newInt; t.id=size; t.oper=oper_assign;
      codeAdd(t,lex);
      int top_stack = stack.indexOfTop();
      stack.push(TOtType::LRInt);
      int iToken=codes.last();
   
      count_value = TInt((mode==mdBits) ? 32 : locVar[id_object].size);
      if ( match(TOtLexem::spSemiColon) ) {
         int val;
         int intCalc=calcExpression(id_TOtRInt,val,0x04);  // id_unknown - !calc, id_void - error, <id_NULL,id_TOtRNum,id_TOtRInt,id_TOtRStr>
         if (intCalc==id_void ) return false;
         if (intCalc==id_NULL) { count_calc = true; }
         if (intCalc==id_TOtRInt) { 
            count_value = ((mode==mdLocal) || (mode==mdIn)) ? min(count_value, intLiter.get(val)) : intLiter.get(val);
            count_calc = true; 
            }

         if ( getIdent(lex_count) ) { 
            locVar[id_count].name=name_count=getText(lex_count); locVar[id_count].lex=lex_count; 
            if (intCalc==id_NULL) { 
               for (int j=codes.last(); j>iToken; j--) {
                  codes[j].type=TOtProgram::TToken::none;
                  }
               stack.pop(); // expr
               genPushInt(count_value,mdgpvNone);
               }
            count_calc = false;
            }
         }
      else {
         count_calc = true;
         }
      if (count_calc) { // code(calc)
         for (int j=token_bit_count+1; j<=codes.last(); j++) {
            codes[j].type=TOtProgram::TToken::none;
            }
         while (stack.indexOfTop() > top_stack) stack.pop();
         locVar.pop();
         blocks.decLocal(var_count.size);
         }
      else {
         if (!voidBinaryOperator(token_bit_count,"=",iToken,lex.ofsMain())) {
            if (errCount) return false;
            errorInvalidOperator("=", lex_foreach, 0x03); return false;
            }
         }
      }
   else if (mode!=mdCursor) { // ident
      if ( match(TOtLexem::spSemiColon) ) {
         if (!getIdentWithError(lex_type_count)) return false;
         name_type_count=getText(lex_type_count); yes_name_type_count=true;
         if ( getIdent(lex_count) ) { name_count=getText(lex_count); }
         }
      else if (mode==mdRec) {
         name_type_count="ItemCount";
         }
      else if (mode==mdStringLine) {
         if (way>0) 
            mode=mdStringNext;
         else
            name_type_count="Height";
         }
      else if (mode==mdStringChar) {
         name_type_count="Len";
         }
      else if (mode&mdUserProp) {
         name_type_count="UserPropItemCount";
         }
      else {
         const TRecForeach& first=items[items.low()];
         name_type_count=first.title+TOtFuncProfile::lexCount; lex_type_count=first.lex_title;
         }
      }

   if (!needBracket(TOtLexem::spRightBracket,')')) return false;

   if (mode==mdRec) {
      TOtFuncFinderHolder holder(adventurers); TOtFuncFinder& finder=holder.finder();
      int owner=abs(type_object.origin);
      for (int i=items.low();i<=items.last();i++) {
         TRecForeach& item=items[i];
         bool yes_error=true;
         int field=locStruct.find(owner,item.title);
         if (field) {
            const TLocStruct& loc=locStruct[field];
            if (loc.obj) {
               if (denial_error(loc.obj)) { return false; }
               }
            if (castable(loc.getType(), TOtType(id_TOtArray))) {
               finder.clear();
               finder.param(TOtType(_id_structure,1,-field),codes.last());
               finder.param(TOtType::RInt,codes.last());
               if (!makeproperty(finder,item.lex_title,"Item")) return false;
               item.prop=property.last();
               const TProperty &prop=property[item.prop];
               item.type=prop.result();
               item.loc=field;
               if (prop.fset) {
                  if (!item.type.isStructure())
                     castableToLR(item.type);
                  else
                     item.type.origin=abs(item.type.origin);
                  }
               stack.pop();
               yes_error=false;
               }
            }
         if (yes_error) {
            errorName(lexMess_UnknownIdentify.system(),item.lex_title); return false;
            }
         }
      }
   else if (mode==mdCursor) {
      TOtFuncFinderHolder holder(adventurers); TOtFuncFinder& finder=holder.finder(); TOtFuncProfile& p=finder.p; 
      finder.param(TOtType(id_TOtRPtr,1,id_TDbADataCursor),codes.last());
      if (!makeproperty(finder,lex_foreach,"AtFirst")) return false;
      prop_first=property.last(); stack.pop();
      finder.clear();
      finder.param(TOtType(id_TOtRPtr,1,id_TDbADataCursor),codes.last());
      if (!makeproperty(finder,lex_foreach,"AtLast")) return false;
      prop_last=property.last(); stack.pop();
      finder.clear(); p.name("MoveToFirst");
      finder.param(TOtType(id_TOtRPtr,1,id_TDbADataCursor),codes.last());
      func_first=findAndAddFuncOrFindSimple(finder);
      finder.clear(); p.name("MoveToLast");
      finder.param(TOtType(id_TOtRPtr,1,id_TDbADataCursor),codes.last());
      func_last=findAndAddFuncOrFindSimple(finder);
      finder.clear(); p.name("Move");
      finder.param(TOtType(id_TOtRPtr,1,id_TDbADataCursor),codes.last());
      finder.param(TOtType::RInt,codes.last());
      func_move=findAndAddFuncOrFindSimple(finder);
      result_move=p.result().id;
      if (!func_first || !func_move || !func_last) { errorName(lexMess_UnknownIdentify.system()+" : "+p.name(),lex_object); return false; }

      int owner=abs(type_object.origin);
      for (int i=items.low();i<=items.last();i++) {
         TRecForeach& item=items[i];
         bool yes_error=true;
         int field=locStruct.find(owner,item.title);
         if (field) {
            const TLocStruct& loc=locStruct[field];
            if (loc.obj) {
               if (denial_error(loc.obj)) { return false; }
               }
            if (castable(loc.getType(), TOtType(id_TDbField))) {
               item.type=loc.getType();
               item.loc=field;
               yes_error=false;
               }
            }
         if (yes_error) {
            errorName(lexMess_UnknownIdentify.system(),item.lex_title); return false;
            }
         }
      }
   else if (mode==mdUserPropItem) {
      TRecForeach& item=items[items.low()];
      TProperty prop; prop.user=true;
      prop.fget=id_u_prop; prop.fset=id_u_prop;
      TOtAFunc *func=u_prop.get();
      if (!func) { error(lexMess_UnknownObjectType.system(),item.lex_title); return 0; }
      prop.result(item.type);
      property.add(prop);
      item.prop=property.last();
      if (!item.type.isStructure())
         castableToLR(item.type);
      else
         item.type.origin=abs(item.type.origin);
      }
   else if ((mode==mdUserPropField) || (mode==mdUser_PropField)) {
      int owner=abs(type_object.origin);
      const TLocStruct& loc=locStruct[owner];
      int i_rec, pt;
      if (mode==mdUserPropField) {
         i_rec=loc.obj->findUserProp(u_prop.prop.name);
         pt=loc.obj->getUserPropType(i_rec);
         }
      else {
         i_rec=locStruct.find(owner,u_prop.prop.name);
         pt=TUserData::ptArrRec;
         }
      for (int i=items.low();i<=items.last();i++) {
         TRecForeach& item=items[i];
         int field=0, rt=0;
         if (mode==mdUserPropField) {
            if (!loc.obj->findUserPropField(i_rec,item.title,field) || !loc.obj->getUserPropFieldType(i_rec,field,rt)) {
               field=0;
               }
            }
         else {
            field=locStruct.find(i_rec,item.title);
            if (field && locStruct[field].isProperty) {
               rt=locStruct[field].getType().id;
               }
            else {
               field=0;
               }
            }
         if (field) {
            TOtProgram::TUserProperty u;
            u.prop .type=pt; u.prop .name=u_prop.prop.name;
            u.field.type=rt; u.field.name=item.title;
            switch (rt) {
               case id_TOtArrNum :
               case id_TOtRecNum :
                  u.field.type=TUserData::ptNum;
               case TUserData::ptNum :
                  item.type=id_TOtLRNum;
                  break;
               case id_TOtArrInt :
               case id_TOtRecInt :
                  u.field.type=TUserData::ptInt;
               case TUserData::ptInt :
                  item.type=id_TOtLRInt;
                  break;
               case id_TOtArrStr :
               case id_TOtRecStr :
                  u.field.type=TUserData::ptStr;
               case TUserData::ptStr :
                  item.type=id_TOtLRStr;
                  break;
               case TUserData::ptPtr : {
                  TOtPtrValueArray *a=loc.obj->getUserPropFieldArrPtr(i_rec,field);
                  item.type = a->getPointerType();
                  if (item.type.templateName.len()) {
                     int idTemplate=0;
                     if (!findTemplateWithError(item.type.templateName,idTemplate,item.lex_title)) { return false; }
                     item.type.origin=idTemplate;
                     item.type.id=_id_structure;
                     }
                  } break;
               case id_TOtArrPtr :
               case id_TOtRecPtr : {
                  u.field.type=TUserData::ptPtr;
                  item.type=TOtType::LRPtrObject;
                  } break;
               default:
                  error(lexMess_UnknownObjectType.system(),item.lex_title); 
                  return 0;
               }
            program->props.add(u);
            int find=program->props.last();
   
            TProperty prop;
            prop.user=true; prop.fget=find; prop.fset=find;
            TOtAFunc *func=u.get();
            if (!func) { error(lexMess_UnknownObjectType.system(),item.lex_title); return 0; }
            prop.result(func->result());
            property.add(prop);

            item.prop=property.last();
            if (!item.type.isStructure())
               castableToLR(item.type);
            else
               item.type.origin=abs(item.type.origin);
            }
         else {
            errorName(lexMess_UnknownIdentify.system(),item.lex_title); return false;
            }
         }
      }
   else if ((mode==mdObjUserProp) || (mode==mdObjUser_Prop)) {
      int owner=abs(type_object.origin);
      const TLocStruct& loc=locStruct[owner];
      for (int i=items.low();i<=items.last();i++) {
         TRecForeach& item=items[i];
         int i_prop=0, pt=0;
         if (mode==mdObjUserProp) {
            i_prop=loc.obj->findUserProp(item.title);
            if (i_prop) pt=loc.obj->getUserPropType(i_prop); //user property type
            }
         else {
            i_prop=locStruct.find(owner,item.title);
            if (i_prop && locStruct[i_prop].isProperty) {
               pt=locStruct[i_prop].getType().id;
               }
            else {
               i_prop=0;
               }
            }
         if (i_prop) {
            TOtProgram::TUserProperty u;
            u.prop.type=pt;
            u.prop.name=item.title;
            switch (pt) {
               case id_TOtArrNum :
                  u.prop.type=TUserData::ptArrNum;
               case TUserData::ptArrNum :
                  item.type=id_TOtLRNum;
                  break;
               case id_TOtArrInt :
                  u.prop.type=TUserData::ptArrInt;
               case TUserData::ptArrInt :
                  item.type=id_TOtLRInt;
                  break;
               case id_TOtArrStr :
                  u.prop.type=TUserData::ptArrStr;
               case TUserData::ptArrStr :
                  item.type=id_TOtLRStr;
                  break;
               case TUserData::ptArrPtr : {
                  TOtPtrValueArray *a=loc.obj->getUserPropArrPtr(i_prop);
                  item.type = a->getPointerType();
                  item.type.id=id_TOtLRPtr;
                  if (item.type.templateName.len()) {
                     int idTemplate=0;
                     if (!findTemplateWithError(item.type.templateName,idTemplate,item.lex_title)) { return false; }
                     item.type.origin=idTemplate;
                     item.type.id=_id_structure;
                     }
                  } break;
               case id_TOtArrPtr : {
                  u.prop.type=TUserData::ptArrPtr;
                  item.type=TOtType::LRPtrObject;
                  } break;
               default:
                  error(lexMess_UnknownObjectType.system(),item.lex_title); 
                  return 0;
               }
            program->props.add(u);
            int find=program->props.last();
   
            TProperty prop;
            prop.user=true; prop.fget=find; prop.fset=find;
            TOtAFunc *func=u.get();
            if (!func) { error(lexMess_UnknownObjectType.system(),item.lex_title); return 0; }
            prop.result(func->result());
            property.add(prop);

            item.prop=property.last();
            if (!item.type.isStructure())
               castableToLR(item.type);
            else
               item.type.origin=abs(item.type.origin);
            }
         else {
            errorName(lexMess_UnknownIdentify.system(),item.lex_title); return false;
            }
         }
      }
   else if (mode==mdObject) {
      TOtFuncFinderHolder holder(adventurers); TOtFuncFinder& finder=holder.finder();
      bool yes_keyarr=castable(type_object,TOtType(id_TOtRPtr,1,id_TOtKeyArray));
      for (int i=items.low();i<=items.last();i++) {
         finder.clear();
         finder.param(type_object,codes.last());
         finder.param(TOtType::RInt,codes.last());
         TRecForeach& item=items[i];
         if (!makeproperty(finder,item.lex_title,item.title)) return false;
         int id_prop=property.last();
         const TProperty &prop=property[id_prop];
         item.type=prop.result();
         item.prop=id_prop;
         if (prop.fset && !(yes_keyarr && (item.title=="Key"))) {
            if (!item.type.isStructure())
               castableToLR(item.type);
            else
               item.type.origin=abs(item.type.origin);
            }
         stack.pop();
         }
      }
   else if ((mode==mdLocal) || (mode==mdIn)) {
      for (int i=items.low();i<=items.last();i++) {
         TRecForeach& item=items[i];
         item.type=type_object;
         if (type_object.id==_id_pointer_array) {
            item.type.id=_id_structure;
            }
         else { // _id_local_array
            if (type_object.oblique)
               item.type.id=(type_object.origin<0)?id_TOtRPtr:id_TOtLRPtr;
            else
               item.type.id=type_object.origin;
            }
         }
      }
   else if (mode & mdString) {
      TRecForeach& item=items[1];
      TOtFuncFinderHolder holder(adventurers); TOtFuncFinder& finder=holder.finder();
      finder.param(type_object,codes.last());
      TOtType result;
      if (mode==mdStringLine) {
         finder.param(TOtType::RInt,codes.last());
         finder.p.name("GetLine");
         item.type=id_TOtRStr; result=id_TOtRStr;
         }
      else if (mode==mdStringNext) {
         finder.param(TOtType::LRInt,codes.last());
         finder.param(TOtType::LStr,codes.last());
         finder.p.name("GetNextLine");
         item.type=id_TOtRStr; result=id_TOtRInt;
         }
      else { // mdStringChar
         finder.param(TOtType::RInt,codes.last());
         finder.p.name("GetItem");
         item.type=id_TOtRInt; result=id_TOtRInt;
         }
      func_item=findAndAddFuncOrFindSimple(finder);
      if (!func_item || !castable(finder.result(), result)) {
         error(lexMess_InvalidObjectType.system(),lex_type_count); return false;
         }
      }
   else if (mode==mdBits) {
      TRecForeach& item=items[1];
      item.type=id_TOtRInt;
      TLocVar var_field(item.field,item.type); var_field.lex=item.lex_field;
      item.var=locVar.push(var_field);
      t.type=TOtProgram::TToken::newInt; t.id=1; t.oper=oper_assign;
      codeAdd(t,item.lex_field);
      TInt bit(1);
      if ((way < 0) && count_calc) bit = TInt(bit << (count_value - TInt(1)));                                    \
      genPushInt(bit,mdgpvNoStack,-oper_assign_Int);
      if ((way < 0) && !count_calc) {
         genPushVar(-item.var,var_field.lex,mdgpvNoStack);
         genPushVar(-id_count,lex_count,mdgpvNoStack);
         genPushInt(TInt(1),mdgpvNoStack,oper_minus_Int);
         t.type=TOtProgram::TToken::operStack; t.id=0; t.oper=-oper_shlassign_Int;
         codeAdd(t,lex_count);
         }
      }

   // count(func)
   if ((mode==mdObject) || (mode==mdRec) || (mode&mdUserProp)) {
      TOtFuncFinderHolder holder(adventurers); TOtFuncFinder& finder=holder.finder();
      finder.param(type_object,codes.last());
      if (mode&mdUserProp) finder.param(TOtType::RStr,codes.last());
      if (!makeproperty(finder, lex_type_count, name_type_count, false)) {
         bool yes_error = true;
         if ((mode == mdObject) && !yes_name_type_count) {
            const TRecForeach& first_item = items[items.low()];
            const TProperty &prop = property[first_item.prop];
            int fget = prop.fget;
            if (fget > 0) {
               const TProgramTable& table = program->table.object();
               const T_Array<TProgramTable::TFuncPtr, TArray::aoMemShift>&   program_func = table.func;
               const TProgramTable::TFuncPtr& func_ptr = program_func[fget];
               if (func_ptr.func) {
                  const TOtPropertyList::TRec* rec = TOtPropertyList::find(func_ptr.func);
                  if (rec && (rec->type & TOtPropertyList::prCount1)) {
                     TStr name = rec->func[TOtPropertyList::fiCount1]->profile().name();
                     name.remove(0, 3);
                     if (!makeproperty(finder, lex_type_count, name)) return false;
                     yes_error = false;
                     }
                  }
               }
            }
         if (yes_error) {
            errorFuncNotFind(finder, lex_type_count);
            return false;
            }
         }
      if (!castable(stack[0],TOtType::RInt)) {
         error(lexMess_InvalidIndexProperty.system(),lex_type_count); return false;
         }
      prop_count=property.last();
      stack.pop();
      }
   else if ((mode&md_Count) && (mode & mdString)) {
      TOtFuncFinderHolder holder(adventurers); TOtFuncFinder& finder=holder.finder();
      finder.param(type_object,codes.last()); finder.p.name(name_type_count);
      prop_count=findAndAddFuncOrFindSimple(finder);
      if (!prop_count) {
         error(lexMess_InvalidObjectType.system(),lex_type_count); return false;
         }
      }

   // count(code(var))
   if ((mode&md_Count) && (mode!=mdBits) && (mode!=mdLocal) && (mode!=mdIn)) {
      TLocVar var_count(name_count,TOtType::LRInt); var_count.lex=lex_count;
      id_count=locVar.push(var_count);
      t.type=TOtProgram::TToken::newInt; t.id=size; t.oper=oper_assign;
      codeAdd(t,var_count.lex);
      if ((mode==mdObject) || (mode==mdRec) || (mode&mdUserProp)) {
         genPushVar(-id_object,lex_object,mdgpvNoStack);
         if (mode&mdUserProp) { 
            const TRecForeach& first=items[items.low()];
            TOtProgram::TToken t_str; t_str.type=TOtProgram::TToken::pushStr;
            t_str.id=addStrLiter(((mode==mdObjUserProp) || (mode==mdObjUser_Prop))?first.title:u_prop.prop.name);
            codeAdd(t_str);
            }
         const TProperty &pr=property[abs(prop_count)];
         pr.make(t,0x01);
         codeAdd(t,var_count.lex);
         }
      else if (mode & mdString) {
         genPushVar(-id_object,lex_object,mdgpvNoStack);
         t.type=TOtProgram::TToken::callFunc; t.id=prop_count; t.oper=oper_None;
         codeAdd(t);
         }
      t.type=TOtProgram::TToken::operStack; t.id=0; t.oper=-oper_assign_Int;
      codeAdd(t,var_count.lex);
      }
   if (mode==mdStringNext) { // int pos = 1;
      TLocVar var_count(name_count,TOtType::LRInt); var_count.lex=lex_count;
      id_count=locVar.push(var_count); // pos
      t.type=TOtProgram::TToken::newInt; t.id=1; t.oper=oper_assign;
      codeAdd(t,var_count.lex);
      count_value = 1; // beg pos
      genPushInt(count_value,mdgpvNoStack,-oper_assign_Int);
      }

   // index
   int id_index=0;
   if ((mode&md_Count) || yes_index) {
      TLocVar var_index(name_index,TOtType::LRInt); var_index.lex=lex_index;
      id_index=locVar.push(var_index);
      t.type=TOtProgram::TToken::newInt; t.id=size; t.oper=((way<0)&&(mode&md_Count))?oper_assign:oper_None;
      codeAdd(t,var_index.lex);
      if ((way<0)&&(mode&md_Count)) {
         if (count_calc) 
            genPushInt(count_value,mdgpvNoStack,-oper_assign_Int);
         else
            genPushVar(-id_count,lex_count,mdgpvNoStack,-oper_assign_Int);
         }
      }

   if (mode==mdRec) {
      for (int i=items.low();i<=items.last();i++) {
         TRecForeach& item=items[i];
         TLocVar var_rec(EMPTY_STR,TOtType(id_TOtRPtr,1,id_TOtRec)); var_rec.lex=item.lex_field;
         item.arr=locVar.push(var_rec);
         t.type=TOtProgram::TToken::newPtr; t.id=size; t.oper=oper_assign;
         codeAdd(t,var_rec.lex);
         genPushVar(-id_object,lex_object,mdgpvNoStack);
         if (!genPushFieldStruct(loc_object,item.loc,item.lex_title,0,mdgfsNoStack)) return false;
         t.type=TOtProgram::TToken::operStack; t.id=0; t.oper=-oper_assign_Ptr;
         codeAdd(t,var_rec.lex);
         }
      }
   else if (mode==mdCursor) {
      for (int i=items.low();i<=items.last();i++) {
         TRecForeach& item=items[i];
         bool yes_value=castable(item.type,TOtType::LRNum) || castable(item.type,TOtType::LRInt) || castable(item.type,TOtType::LRStr);
         TLocVar var_rec(item.field,yes_value?item.type:TOtType(id_TOtRPtr,1,item.type.id)); var_rec.lex=item.lex_field;
         item.arr=locVar.push(var_rec);
         if (yes_value) {
            genPushVar(-id_object,lex_object,mdgpvNoStack);
            if (!genPushFieldStruct(loc_object,item.loc,item.lex_title,0,mdgfsNoStack)) return false;
            t.type=TOtProgram::TToken::newPtr; t.id=size; t.oper=oper_assign_Object;
            codeAdd(t,var_rec.lex);
            }
         else {
            t.type=TOtProgram::TToken::newPtr; t.id=size; t.oper=oper_assign;
            codeAdd(t,var_rec.lex);
            genPushVar(-id_object,lex_object,mdgpvNoStack);
            if (!genPushFieldStruct(loc_object,item.loc,item.lex_title,0,mdgfsNoStack)) return false;
            t.type=TOtProgram::TToken::operStack; t.id=0; t.oper=-oper_assign_Ptr;
            codeAdd(t,var_rec.lex);
            }
         }
      // cursor => MoveToWay()
      genPushVar(-id_object,lex_object,mdgpvNoStack);
      t.type=TOtProgram::TToken::callFunc; t.id=(way>0)?func_first:func_last; t.oper=oper_None;
      codeAdd(t);
      }

   if (mode==mdStringNext) {
      TRecForeach& item=items[1];
      TLocVar var_field(item.field,item.type);
      item.var=locVar.push(var_field);
      t.type=TOtProgram::TToken::newStr; t.id=1; t.oper=oper_None;
      codeAdd(t,item.lex_field);
      }

   gotoForward.push();                             //        break => iEnd
   gotoBackward.push();                            //        continue => iSt2
   gotoLabel1.push();

   if ((mode&md_Count) || yes_index) {
      int oper=oper_None;
      if ((mode&md_Count))
         oper=(way>0)? oper_plus_plus_Int:cast_not_Int;
      else 
         oper=(way>0)?-oper_plus_plus_Int:-oper_minus_minus_Int;
      genPushVar(-id_index,lex_index,mdgpvNoStack,oper);
      }

   if ((mode&md_Count) && (way>0)) {
      if (count_calc) 
         genPushInt(count_value,mdgpvNoStack,oper_great_Int);
      else
         genPushVar(-id_count,lex_count,mdgpvNoStack,oper_great_Int);
      }

   if (mode==mdCursor) {
      genPushVar(-id_object,lex_object,mdgpvNoStack);
      const TProperty &pr=property[(way>0)?prop_last:prop_first];
      t.type=TOtProgram::TToken::callFunc; t.id=pr.fget; t.oper=oper_None;
      codeAdd(t,lex_object);
      }
   if (mode!=mdStringNext) {
      stack.push(TOtType::RInt);
      falseChain.push();
      falseChain.add(genIf(1));                       //        goto => end
      }

   if (mode==mdBits) {
      TRecForeach& item=items[1];
      genPushVar(-id_object,lex_object,mdgpvNoStack);
      genPushVar(-item.var,item.lex_field,mdgpvNoStack,-oper_and_Int);
      stack.push(TOtType::RInt);
      gotoBackward.add(genIf(-1));                 //        goto => continue
      }

   blocks.push(TOtlBlock::blBlock);

   if ((mode!=mdCursor) && (mode!=mdBits)){
      for (int i=items.low();i<=items.last();i++) {
         TRecForeach& item=items[i];
         TLocVar var_field(item.field,item.type); var_field.lex=item.lex_field;
         if (mode!=mdStringNext) {
            item.var=locVar.push(var_field);
            }
         if ((mode==mdLocal) || (mode==mdIn)) {
            genPushVar(-id_object,lex_object,mdgpvNoStack);
            genPushVar(-id_index,lex_index,mdgpvNoStack,oper_index);
            }
         else if ((mode==mdObject) || (mode==mdRec) || (mode&mdUserProp)) {
            if (mode==mdRec) {
               genPushVar(-item.arr,var_field.lex,mdgpvNoStack);
               }
            else {
               genPushVar(-id_object,lex_object,mdgpvNoStack);
               }
            genPushVar(-id_index,lex_index,mdgpvNoStack,cast_ToVal);
            const TProperty &pr=property[item.prop];
            pr.make(t,0x13); // 0x10 -> TToken::delVar
            codeAdd(t,var_field.lex);
            }
         else if (mode&mdString) {
            if (mode==mdStringNext) {
               genPushVar(-id_object,lex_object,mdgpvNoStack);    // str
               genPushVar(-id_count,lex_count,mdgpvNoStack);      // pos
               genPushVar(-item.var,item.lex_field,mdgpvNoStack); // sub
               t.type=(func_item>0)?TOtProgram::TToken::callFunc:TOtProgram::TToken::simpleOperator; 
               t.id=(func_item>0)?func_item:-func_item; t.oper=oper_None;
               codeAdd(t,var_field.lex);
               stack.push(TOtType::RInt);
               falseChain.push();
               falseChain.add(genIf(-1));                         // goto => end
               }
            else {
               t.type=(mode==mdStringLine)?TOtProgram::TToken::newStr:TOtProgram::TToken::newInt; t.id=1; t.oper=oper_assign;
               codeAdd(t,item.lex_field);
               genPushVar(-id_object,lex_object,mdgpvNoStack);
               genPushVar(-id_index,lex_index,mdgpvNoStack);
               t.type=(func_item>0)?TOtProgram::TToken::callFunc:TOtProgram::TToken::simpleOperator; 
               t.id=(func_item>0)?func_item:-func_item; t.oper=oper_None;
               codeAdd(t,var_field.lex);
               t.type=TOtProgram::TToken::operStack; t.id=0; t.oper=(mode==mdStringLine)?-oper_assign_Str:-oper_assign_Int;
               codeAdd(t,var_field.lex);
               }
            }
         }
      }

   exerets.push();
   if (!statement_block(TOtlBlock::blBlock)) return false;  // body
   exerets.pop(TExeRet::xeNone);

   if (!blocks.pop()) return false;

   saveLine();

   if ((mode&md_Count) && (way<0)) {
      gotoBackward.popLabel();                    //        continue => --
      genPushVar(-id_index,lex_index,mdgpvNoStack,-oper_minus_minus_Int);
      }
   else if (mode==mdCursor) {
      gotoBackward.popLabel();                    //        continue => Move()
      genPushVar(-id_object,lex_object,mdgpvNoStack);
      genPushInt(TInt((way>0)?1:-1),mdgpvNoStack);
      t.type=TOtProgram::TToken::callFunc; t.id=func_move; t.oper=oper_None;
      codeAdd(t);
      if (result_move != id_void) { 
         genPop(false,0);
         }
      }
   else if (mode==mdBits) {
      gotoBackward.popLabel();
      }
   else {
      gotoBackward.pop();                        //        continue => ++
      }

   if (mode==mdBits) {
      TRecForeach& item=items[1];
      genPushVar(-item.var,item.lex_field,mdgpvNoStack);
      genPushInt(TInt(1),mdgpvNoStack,(way < 0) ? -oper_ushrassign_Int : -oper_shlassign_Int);
      }

   gotoLabel1.add(genGoTo());                    //        goto => iSt2
   gotoLabel1.pop();
   falseChain.popLabel();
   if (!blocks.pop()) return false;
   gotoForward.popLabel();                       //        break => end: label

   restoreLine();
   TREE_LEAVE(trForeach)
   return true;
}

class TCatchCoveringArray : public T_BoundedArray<TOtProgram::TCatch, 1, 10, -20, TArray::aoMem> {
public:
   TCatchCoveringArray(TOtTranslator* t) :translator(t) {}
public:
   bool covering(const TOtProgram::TCatch&) const;
   bool merge(const TOtProgram::TCatch&);
   bool AddCatch(dword b, dword e);
protected:
   TOtTranslator* translator;
};

bool TCatchCoveringArray::covering(const TOtProgram::TCatch& c) const
{
   for (int i = low(); i <= last(); i++ ) {
      if ((*this)[i].control(c)) return true;
   }
   return false;
}

bool TCatchCoveringArray::merge(const TOtProgram::TCatch& c)
{
   bool ret = false;
   for (int i = low(); i <= last(); i++) {
      if ((*this)[i].merge(c)) ret = true;
   }
   return ret;
}

bool TCatchCoveringArray::AddCatch(dword b, dword e)
{
   TOtProgram::TCatch catch_(b, e, 0);
   if (catch_.valid()) {
      if (covering(catch_)) {
         translator->warning(lexMess_WarningUnreachable.system());
         }
      else {
         if (!merge(catch_)) add(catch_);
         }
      }
   else {
      translator->error(lexMess_RangeError.system()); return false;
      }
   return true;
}

bool TOtTranslator::stTry()
{
   TREE_MARKER(xel) //  Try
   trueChain.push();
   gotoLabel1.push();
   gotoLabel2.push();
   int finally=genTry(1);
   trueChain.add(genGoTo());
   gotoLabel1.setLabel();
   exerets.push();
   if (!statement_compound(TOtlBlock::blTry)) return false;
   genTry(0);
   saveLine();
   gotoLabel2.add(genGoTo());
   bool yesCatch=false;
   TCatchCoveringArray covering(this);
   TREE_MARKER(0) //  List
   while (match(TOtLexem::rvCatch)) {
      TREE_MARKER(xel) //  Catch
      yesCatch=true;
      exerets.exec(TExeRet::xeEnd);
      exerets.exec(TExeRet::xeBeg);
      trueChain.popLabel();
      restoreLine();
      trueChain.push();
      if (!needBracket(TOtLexem::spLeftBracket, '(')) return false;
      int nThrow=0;
      bool dia=false;
      if (match(TOtLexem::spEllipsis)) {
         if (!covering.AddCatch(0, 0)) return false;
         TREE_PUSH(trNone,xel)
         }
      else if (match(TOtLexem::spAllFours)) {
         if (!covering.AddCatch(0, MAXDWORD)) return false;
         TREE_PUSH(trNone,xel)
         nThrow=-128;
         }
      else {
         TREE_MARKER(xel) //  List
         do {
            bool int_beg = false, int_end = false;
            dword val_beg = 0, val_end = 0; int value = 0;
            int calc = calcExpression(id_TOtRInt,value,0);
            if (calc == id_void) return false;
            if (!TOtMetaInfo::castable(stack[0],TOtType::RInt)) {
               error(lexMess_NoIntType.system()); return false;
               }
            if (calc == id_TOtRInt) {
               val_beg = intLiter.get(value).getUInt32();
               int_beg = true;
               }
            nThrow++;
            if ((nThrow==1) && matchNo(TOtLexem::spRightBracket)) {
               if (int_beg) {
                  if (!covering.AddCatch(val_beg, val_beg)) return false;
                  }
               stack.pop();
               break;
               }
            dia=true;
            if (match(TOtLexem::spEllipsis)) {
               TOtLexem lek=xel;
               calc = calcExpression(id_TOtRInt, value, 0);
               if (calc == id_void) return false;
               if (!TOtMetaInfo::castable(stack[0],TOtType::RInt)) {
                  error(lexMess_NoIntType.system()); return false;
                  }
               if (calc == id_TOtRInt) {
                  val_end = intLiter.get(value).getUInt32();
                  int_end = true;
               }
               if (int_beg && int_end) {
                  if (!covering.AddCatch(val_beg, val_end)) return false;
                  }
               TREE_TRANSVECTION(trBinaryOper,lek,2)
               }
            else {
               if (int_beg) {
                  if (!covering.AddCatch(val_beg, val_beg)) return false;
                  }
               genDual();
               }
            stack.pop();
            stack.pop();
            }
         while ( match(TOtLexem::spComma) );
         TREE_LEAVE(trList)
         }
      if (!needBracket(TOtLexem::spRightBracket,')')) return false;
      if (nThrow>127) {
         error(lexMess_BadCountParameters.system()); return false;
         }
      trueChain.add(genCatch(dia?-nThrow:nThrow));
      if (!statement_compound(TOtlBlock::blCatch)) return false;
      genThrow(-1);
      saveLine();
      gotoLabel2.add(genGoTo());
      TREE_LEAVE(trCatch)
      }
   saveLine();
   TREE_LEAVE(trList)
   exerets.exec(TExeRet::xeEnd);
   exerets.pop();
   exerets.Unreachable();
   trueChain.popLabel();
   gotoLabel1.add(genGoTo());
   gotoLabel1.pop();
   gotoLabel2.popLabel();
   restoreLine();
   exerets.push();
   if (match(TOtLexem::rvFinally)) {
      TREE_MARKER(xel) //  Finally
      genNone();
      codes[finally].id=codes.last();
      if (!statement_compound(TOtlBlock::blFinally)) return false;
      genTry(-1);
      TREE_LEAVE(trFinally)
      }
   else {
      if (!yesCatch) { error(lexMess_NoCatch.system()); return false; }
      }
   exerets.pop(TExeRet::xeReturn);
   TREE_LEAVE(trTry)
   return true;
}

bool TOtTranslator::stThrow()
{
   TREE_MARKER(xel) //  throw code [,info [,"mess" [,"ext" [,this]]]];
   int yes=0;
   if (!match(TOtLexem::spSemiColon)) {
      yes++; int iBeg=codes.last();
      if (!notVoidExpression() || !prefixExpressionOperator(iBeg)) return false;
      if (!TOtMetaInfo::castable(stack[0],TOtType::RInt)) {
         error(lexMess_NoIntType.system()); return false;
         }
      if (match(TOtLexem::spComma)) {
         yes++; int iBeg_1=codes.last();
         if (!notVoidExpression() || !prefixExpressionOperator(iBeg_1)) return false;
         if (!TOtMetaInfo::castable(stack[0],TOtType::RInt)) {
            error(lexMess_NoIntType.system()); return false;
            }
         if (match(TOtLexem::spComma)) {
            yes++; int iBeg_2=codes.last();
            if (!notVoidExpression() || !prefixExpressionOperator(iBeg_2)) return false;
            if (!TOtMetaInfo::castable(stack[0],TOtType::RStr)) {
               error(lexMess_NoStrType.system()); return false;
               }
            if (match(TOtLexem::spComma)) {
               yes++; int iBeg_3=codes.last();
               if (!notVoidExpression() || !prefixExpressionOperator(iBeg_3)) return false;
               if (TOtMetaInfo::castable(stack[0],TOtType::RStr)) {
                  if (match(TOtLexem::spComma)) {
                     yes++; int iBeg_4=codes.last();
                     if (!notVoidExpression() || !prefixExpressionOperator(iBeg_4)) return false;
                     if (!castable(stack[0],TOtType(id_TOtRPtr))) {
                        error(lexMess_NoPointer.system()); return false;
                        }
                     }
                  }
               else if (!castable(stack[0],TOtType(id_TOtRPtr))) {
                  error(lexMess_NoPointer.system()); return false;
                  }
               }
            }
         }
      if (!needBracket(TOtLexem::spSemiColon,';')) return false;
      }
   genThrow(yes);
   while (yes--) {
      stack.pop();
      }
   exerets.exec(TExeRet::xeReturn);
   TREE_LEAVE(trThrow)
   return true;
}

bool TOtTranslator::stFork()
{
   TREE_MARKER(xel) //  Fork
   if (!needBracket(TOtLexem::spLeftBracket, '(')) return false;
   TREE_MARKER(xel) //  List
   int param=0;
   do {
      int iBeg=codes.last();
      if (!notVoidExpression()) return false;
      if (!prefixExpressionOperator(iBeg)) return false;
      if (!TOtMetaInfo::castable(stack[0],TOtType::RInt)) {
         error(lexMess_NoIntType.system()); return false;
         }
      stack.pop();
      param++;
      }
   while ( match(TOtLexem::spComma) );
   TREE_LEAVE(trList)
   if (!needBracket(TOtLexem::spRightBracket,')')) return false;
   if (param > 2) { error(lexMess_BadCountParameters.system()); return false;}
   gotoLabel1.push();
   TOtProgram::TToken t;
   t.type=TOtProgram::TToken::stFork;
   t.oper=param;
   t.id=0;
   codeAdd(t);
   gotoLabel1.add(codes.last());
   if (!statement_compound(TOtlBlock::blFork)) return false;
   t.oper=-1;
   t.id=0;
   codeAdd(t);
   gotoLabel1.popLabel();
   TREE_LEAVE(trFork)
   return true;
}
bool TOtTranslator::stSemaphore()
{
   blocks.push(TOtlBlock::blBlock);
   TREE_MARKER(xel) //  Semaphore
   TREE_MARKER(xel) //  List
   int param=0;
   if (!needBracket(TOtLexem::spLeftBracket,'(')) return false;

   int iSem=codes.last();
   if (!notVoidExpression()) return false;
   if (!prefixExpressionOperator(iSem)) return false;
   bool isdir=false;
   if (castable(stack[0],TOtType::RPtrDir)) {
      isdir=true;
      }
   else if (!TOtMetaInfo::castable(stack[0],TOtType(id_TOtRPtr,1,id_TOtSemaphore))) {
      error(lexMess_InvalidObjectType.system()+" "+TOtMetaInfo::name(castable(stack[0]))); return false;
      }
   stack.pop(); param++;

   if (match(TOtLexem::spComma)) {
      int iTime=codes.last();
      if (!notVoidExpression()) return false;
      if (!prefixExpressionOperator(iTime)) return false;
      if (!TOtMetaInfo::castable(stack[0],TOtType__RNum)) {
         int cast=0;
         if (stack[0]==TOtType__Null) {
            cast=castNULL(TOtType__RNum);
            }
         else if (TOtMetaInfo::castable(stack[0],TOtType__RInt)) {
            cast=cast_Int2Num;
            }
         else {
            error(lexMess_InvalidExpression.system()); return false;
            }
         TOtProgram::TToken t;
         t.type=TOtProgram::TToken::castStack;
         t.id=cast;
         t.oper=oper_None;
         codeAdd(t);
         }
      stack.pop(); param++;

      if (!isdir && match(TOtLexem::spComma)) {
         int iMode=codes.last();
         if (!notVoidExpression()) return false;
         if (!prefixExpressionOperator(iMode)) return false;
         if (!TOtMetaInfo::castable(stack[0],TOtType__RInt)) {
            error(lexMess_NoIntType.system()); return false;
            }
         stack.pop(); param++;
         }
      }

   if (!needBracket(TOtLexem::spRightBracket,')')) return false;
   TREE_LEAVE(trList)

   TOtType v(id_unknown);
   TLocVar newV(EMPTY_STR,v);
   locVar.push(newV);

   TOtProgram::TToken t;
   t.type=TOtProgram::TToken::stSemaphore;
   t.id=1;
   t.oper=param|(isdir?0x010:0);
   codeAdd(t);

   trueChain.push();falseChain.push();
   stack.push(TOtType__RInt);
   int iIf=genIf(-1); if (!iIf) return false;
   falseChain.add(iIf);
   trueChain.popLabel(falseChain);

   if (!stThen_Else()) return false;

   TREE_LEAVE(trSemaphore)
   if (!blocks.pop()) return false;
   return true;
}

int  TOtTranslator::calcExpression(int type, int& result, int mode) //   0x01 - error, 0x02 - token=none, 0x04 -  NULL
{
   int ret=id_void; // id_unknown - !calc, id_void - error, <id_NULL,id_TOtRNum,id_TOtRInt,id_TOtRStr> - calc
   int iBeg=codes.last();
   if (!notVoidExpression() || !prefixExpressionOperator(iBeg)) return id_void;
   TString mess; if (mode&0x01) mess=(type==id_TOtRInt)?lexMess_NoIntType.system():lexMess_NoStrType.system();
   if (!TOtMetaInfo::castable(stack[0],TOtType(type)) && !((mode&0x04) && (stack[0]==TOtType__Null))) {
      if (mode&0x01) error(mess); return id_unknown;
      }
   if (mode&0x02) stack.pop();
   int iEnd=codes.last();
   int count=0;
   for (int i=++iBeg;i<=iEnd;i++) {
      TOtProgram::TToken& token=codes[i];
      switch (token.type) {
         case TOtProgram::TToken::none:
         case TOtProgram::TToken::line:
            break;
         case TOtProgram::TToken::pushNULL:
            if ((mode&0x04)==0) {
               if (mode&0x01) error(mess); return id_unknown;
               }
            count++;  ret=id_NULL;    result=0;
            if (mode&0x02) token.type=token.none;
            break;
         case TOtProgram::TToken::pushNum:
            count++;  ret=id_TOtRNum; result=token.id;
            if (mode&0x02) token.type=token.none;
            break;
         case TOtProgram::TToken::pushInt:
            count++;  ret=id_TOtRInt; result=token.id;
            if (mode&0x02) token.type=token.none;
            break;
         case TOtProgram::TToken::pushStr:
            count++;  ret=id_TOtRStr; result=token.id;
            if (mode&0x02) token.type=token.none;
            break;
         default:
            if (mode&0x01) error(mess); return id_unknown;
         }
      }
   if (count!=1) {
      if (mode&0x01) error(mess); return id_unknown;
      }
   return ret;
}

bool TOtTranslator::voidExpression()
{
   trueChain.push();falseChain.push();
   int bpOld=stack.indexOfTop();
   int iBeg=codes.last();

   if (! level0(true) ) return false;
   genValue();

   if (stack.indexOfTop() == bpOld+1) {
      if (!prefixExpressionOperator(iBeg)) return false;
      bool find=false;
      int j=beforeCode(codes.last()+1);
      if (j) {
         TOtProgram::TToken *token=&codes[j];
         if ((token->type==TOtProgram::TToken::noneNone) && (j>codes.low())) {
            j--; token=&codes[j];
            }
         if ((token->type==TOtProgram::TToken::simpleOperator) && (token->oper==oper_None)) {
            int id=token->id;
            const TSimpleOperation& type_simple=TSimpleOperation::coll[id];
            while (!find && ++id<=TSimpleOperation::coll.last()) {
               const TSimpleOperation& void_simple=TSimpleOperation::coll[id];
               if ((void_simple.profile.result()==id_void) && (abs(type_simple.profile.compare(void_simple.profile))<=1)) {
                  token->id=id; find=true;
                  }
               }
            FLORA_TRANSLATOR_DUMP_IF(0,
               if (find) {
                  char c[12];
                  sprintf(c,"*%.4d",j);
                  os<<c;
                  printToken(os,*token,false);
                  }
               )
            if (!find && (type_simple.attr() & TSimpleOperation::cEqualOper)) {
               warning(lexMess_WarningAssignment.system()+": ==");
               }
            }
         }
      if (!find)
         genPop();
      else {
         stack.pop();
         }
      }

   trueChain.pop();falseChain.pop();
   return true;
}

bool TOtTranslator::notVoidExpression()
{
   trueChain.push();falseChain.push();

   int bpOld=stack.indexOfTop();

   if (! level0() ) return false;
   genValue();

   int bpDelta=stack.indexOfTop() - bpOld;
   if (bpDelta != 1) { error(lexMess_VoidObject.system()); return false; };

   trueChain.pop();falseChain.pop();
   return true;
}

bool TOtTranslator::jumpExpression(bool comp)
{
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();

   if (! level0() ) return false;
   int bpDelta=stack.indexOfTop() - bpOld;
   if (!trueChain.yesGoTo() && !falseChain.yesGoTo()) {
      if (bpDelta != 1) { error(lexMess_VoidObject.system()); return false; };
      warningAssign();
      TOtType v(stack[0]);
      if (v.isStructureOblique() && (v.origin<0)){
         const TLocStruct& loc=locStruct[abs(v.origin)];
         if (loc.isConst && loc.isPath) {
            warning(lexMess_WarningNeedStar.system());
            }
         }
      if (!isUnary(bpOld) || !prefixOperator(iBeg)) return false;
      int iIf=genIf(-1); if (!iIf) return false;
      falseChain.add(iIf);
      }
   else {
      if (bpDelta != 0) { error(lexMess_InvalidExpression.system()); return false; };
      }

   if (comp) {
      falseChain.popLabel(trueChain);
      }
   else {
      trueChain.popLabel(falseChain);
      }
   return true;
}

bool TOtTranslator::level0(bool mustvoid)
{
   int bpOld=stack.indexOfTop();

   if (! level1(mustvoid) ) { if (!errCount) error(lexMess_InvalidExpression.system()); return false; }

   int bpDelta=stack.indexOfTop() - bpOld;
   if (trueChain.yesGoTo() || falseChain.yesGoTo()) bpDelta++;
   if (bpDelta > 1) { error(lexMess_UndueObject.system()); return false; };
   if (bpDelta < 0) { error(lexMess_VoidObject.system()); return false; };

   return true;
}

bool TOtTranslator::level1(bool mustvoid)           // level2 x= level1
{
   if (exceeding()) return false;
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();

   if (! level2_0() ) return false;

   TOtLexem lek;
   int iToken=codes.last();
   if (match(lek,TOtLexem::lkOperSet) || match(lek,TOtLexem::lkOperVoid)) {
      if (!isVariable()) return false;
      if (! level1() ) return false;
      genValue();
      if (!isBinary(bpOld)) return false;
      nesting--;
      if (mustvoid) {
         if (voidBinaryOperator(iBeg,lek,iToken)) return true;
         if (errCount) return false;
         }
      if (notVoidBinaryOperator(iBeg,lek,iToken)) return true;
      errorInvalidOperator(getText(lek), lek, 0x03); 
      return false;
      }
   nesting--;
   return true;
}

bool TOtTranslator::level2_0()           // level2_QQ ? level1 : level2_0
{

   trueChain.push(); falseChain.push();

   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();

   if (! level2_QQ() ) return false;

   if ( match(TOtLexem::opQuestion) ) {

      TOtLexem lek(xel);
      if (!trueChain.yesGoTo() && !falseChain.yesGoTo()) {
         if (!isUnary(bpOld) || !prefixOperator(iBeg)) return false;
         int iIf=genIf(-1); if (!iIf) return false;
         falseChain.add(iIf);
         }
      trueChain.popLabel(falseChain);

      trueChain.push(); falseChain.push();
      int iOne=codes.last();
      if (! level1() ) return false;
      genValue();
      if (!isUnary(bpOld) || !prefixOperator(iOne)) return false;
      int eOne=codes.last();
      trueChain .pop(); falseChain.pop();
      int oneNone=genNone(); // cast(1 -> 2)

      gotoLabel1.push();
      gotoLabel1.add(genGoTo());
      falseChain.popLabel();
      if (!needBracket(TOtLexem::spColon,':')) return false;

      trueChain.push(); falseChain.push();
      int iTwo=codes.last();
      if (! level2_0() ) return false;
      genValue();
      if (!isBinary(bpOld) || !prefixOperator(iTwo)) return false;
      int eTwo=codes.last();
      trueChain .pop(); falseChain.pop();
      int twoNone=genNone(); // cast(2 -> 1)
      genNone();             // !optimize
      gotoLabel1.popLabel();

      TOtType twoOp=stack[0];
      stack.pop();
      TOtType oneOp=stack[0];
      stack.pop();
      bool err=false;
      int  castOne=0, weightOne=0, castTwo=0, weightTwo=0;
      bool one2two=castable(oneOp,twoOp,castOne,weightOne);
      bool two2one=castable(twoOp,oneOp,castTwo,weightTwo);
      if (one2two && !castOne) {      // 1 -> 2
         stack.push(twoOp);
         }
      else if (two2one && !castTwo) { // 2 -> 1
         stack.push(oneOp);
         }
      else if (twoOp==TOtType__Null && oneOp!=TOtType__Null) { // 1 <- NULL
         TOtProgram::TToken& token=codes[beforeCode(eTwo+1)];
         TOtType join=castable(oneOp);
         if (token.type==token.pushNULL && token.obj.id==id_void && TOtMetaInfo::castableToR(join)) {
            token.obj.id=join.id;
            stack.push(oneOp);
            }
         else
            err=true;
         }
      else if (oneOp==TOtType__Null && twoOp!=TOtType__Null) { // NULL -> 2
         TOtProgram::TToken& token=codes[beforeCode(eOne+1)];
         TOtType join=castable(twoOp);
         if (token.type==token.pushNULL && token.obj.id==id_void && TOtMetaInfo::castableToR(join)) {
            token.obj.id=join.id;
            stack.push(twoOp);
            }
         else
            err=true;
         }
      else if (one2two || two2one) {
         if ((one2two && two2one) && (weightOne <= weightTwo) || !two2one) { // 1 -> 2
            TOtProgram::TToken& token=codes[oneNone];
            token.type=token.castStack; token.id=castOne;
            stack.push(twoOp);
            }
         else {                        // 2 -> 1
            TOtProgram::TToken& token=codes[twoNone];
            token.type=token.castStack; token.id=castTwo;
            stack.push(oneOp);
            }
         }
      else {
         err=true;
         }
      if (err) {
         TString s(lexMess_ObjectTypesMismatch.system());
         s+=" "; s+=TOtMetaInfo::name(castable(oneOp));
         s+=" "; s+=" : ";
         s+=" "; s+=TOtMetaInfo::name(castable(twoOp));
         error(s);
         return false;
         }

      TREE_TRANSVECTION(trQuestion,lek,3)
      }
   else {
      trueChain .merge(); falseChain.merge();
      }

   return true;
}

bool TOtTranslator::level2_QQ()        // level2 ?? level1
{

   trueChain.push(); falseChain.push();

   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();

   if (! level2() ) return false;

   if (match(TOtLexem::opQQuestion)) {

      TOtLexem lek(xel);

      TREE_TRANSVECTION(trQuestion,lek,2)
      }
   else {
      trueChain .merge(); falseChain.merge();
      }

   return true;
}

bool TOtTranslator::level2()           // level3 || level3
{
   falseChain.push();
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();

   if (! level3() ) return false;

   int tokenIf=0;
   bool yesOr=false;
   TOtLexem lek;
   while ( match(lek,TOtLexem::opOrLogic) ) {
      warningAssign();
      if (!falseChain.yesGoTo()  && (trueChain.ward[0] == tokenIf)) {
         if (!isUnary(bpOld) || !prefixOperator(iBeg)) return false;
         int iIf=genIf(1); if (!iIf) return false;
         trueChain.add(iIf);
         }
      falseChain.popLabel(trueChain);
      falseChain.push();
      tokenIf=trueChain.ward[0];
      trueChain.push();
      if (! level3() ) return false;
      trueChain.merge();
      yesOr=true;
      TREE_TRANSVECTION(trBinaryOper,lek,2)
      }
   if (yesOr) {
      if (!falseChain.yesGoTo()  && (trueChain.ward[0] == tokenIf)) {
         if (!isUnary(bpOld) || !prefixOperator(iBeg)) return false;
         int iIf=genIf(1); if (!iIf) return false;
         trueChain.add(iIf);
         }
      }
   falseChain.merge();
   return true;
}

bool TOtTranslator::level3()           // level4 && level4
{
   trueChain.push();
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   if (! level4() ) return false;
   int tokenIf=0;
   bool yesAnd=false;
   TOtLexem lek;
   while ( match(lek,TOtLexem::opAndLogic) ) {
      warningAssign();
      if (!trueChain.yesGoTo() && (falseChain.ward[0] == tokenIf)) {
         if (!isUnary(bpOld) || !prefixOperator(iBeg)) return false;
         int iIf=genIf(-1); if (!iIf) return false;
         falseChain.add(iIf);
         }
      trueChain.popLabel(falseChain);
      trueChain.push();
      tokenIf=falseChain.ward[0];
      falseChain.push();
      if (! level4() ) return false;
      falseChain.merge();
      yesAnd=true;
      TREE_TRANSVECTION(trBinaryOper,lek,2)
      }
   if (yesAnd) {
      if (!trueChain.yesGoTo() && (falseChain.ward[0] == tokenIf)) {
         if (!isUnary(bpOld) || !prefixOperator(iBeg)) return false;
         int iIf=genIf(-1); if (!iIf) return false;
         falseChain.add(iIf);
         }
      }
   trueChain.merge();
   return true;
}

bool TOtTranslator::level4()           // level5 | level5
{
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   if (! level5() ) return false;
   TOtLexem lek;
   while ( match(lek,TOtLexem::opOr) ) {
      genValue();
      int iToken=codes.last();
      if (! level5() ) return false;
      genValue();
      if (!isBinary(bpOld) || !binaryOperator(iBeg,lek,iToken)) return false;
      }
   return true;
}

bool TOtTranslator::level5()           // level6 ^ level6
{
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   if (! level6() ) return false;
   TOtLexem lek;
   while ( match(lek,TOtLexem::opXor) ) {
      genValue();
      int iToken=codes.last();
      if (! level6() ) return false;
      genValue();
      if (!isBinary(bpOld) || !binaryOperator(iBeg,lek,iToken)) return false;
      }
   return true;
}

bool TOtTranslator::level6()           // level7 & level7
{
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   if (! level7() ) return false;
   TOtLexem lek;
   while ( match(lek,TOtLexem::opAnd) ) {
      genValue();
      int iToken=codes.last();
      if (! level7() ) return false;
      genValue();
      if (!isBinary(bpOld) || !binaryOperator(iBeg,lek,iToken)) return false;
      }
   return true;
}

bool TOtTranslator::level7()    // level8 == level8, != level8
{
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   if (! level8() ) return false;
   TOtLexem lek;
   while ( match(lek,TOtLexem::lkOperEqu) ) {
      genValue();
      int iToken=codes.last();
      if (! level8() ) return false;
      genValue();
      if (!isBinary(bpOld) || !binaryOperator(iBeg,lek,iToken)) return false;
      lek=lex;
   }
   return true;
}

bool TOtTranslator::level8()    // level9 <= level9, >= level9, > level9, > level9
{
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   if (! level9() ) return false;
   TOtLexem lek;
   while ( match(lek,TOtLexem::lkOperComp) ) {
      genValue();
      int iToken=codes.last();
      if (! level9() ) return false;
      genValue();
      if (!isBinary(bpOld) || !binaryOperator(iBeg,lek,iToken)) return false;
      lek=lex;
   }
   return true;
}

bool TOtTranslator::level9()    // level10 >> level10, << level10
{
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   if (! level10() ) return false;
   TOtLexem lek;
   while (match(lek,TOtLexem::opRightShift) || match(lek,TOtLexem::opLeftShift)) {
      int iToken=codes.last();
      genValue();
      if (! level10() ) return false;
      genValue();
      if (!isBinary(bpOld)) return false;
      if (!notVoidBinaryOperator(iBeg,lek,iToken)) {
         if (errCount) return false;
         if (!binaryOperator(iBeg,lek,iToken)) return false;
         }
      lek=lex;
      }
   return true;
}

bool TOtTranslator::level10()    // level11 + level11, - level11
{
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   if (! level11() ) return false;
   TOtLexem lek;
   while (match(lek,TOtLexem::opAdd) || match(lek,TOtLexem::opSub)) {
      int iToken=codes.last();
      genValue();
      if (! level11() ) return false;
      genValue();
      if (!isBinary(bpOld) || !binaryOperator(iBeg,lek,iToken)) return false;
      lek=lex;
      }
   return true;
}

bool TOtTranslator::level11()    // level12 * level12, / level12, % level12
{
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   if (! level12_0() ) return false;
   TOtLexem lek;
   while (match(lek,TOtLexem::opMulti) || match(lek,TOtLexem::opDiv) || match(lek,TOtLexem::opMod)) {
      int iToken=codes.last();
      genValue();
      if (! level12_0() ) return false;
      genValue();
      if (!isBinary(bpOld) || !binaryOperator(iBeg,lek,iToken)) return false;
      lek=lex;
      }
   return true;
}

bool TOtTranslator::level12_0()    // level12 ? {level1,level1,level12,...}
{
   int iBeg=codes.last();
   if (! level12() ) return false;
   OnRestitution(); 
   bool yes_not=match(TOtLexem::opNot);
   bool yes_in=match(TOtLexem::opQuestion) && match(TOtLexem::spLeftCramp);
   OffRestitution(); 
   if ( yes_in ) {
      if (stack.empty()) {
         error(lexMess_InvalidObjectType.system());
         return false;
         }
      TOtType type_in(stack[0]),type_r(type_in);
      if (!castableToR(type_r)) {
         error(lexMess_InvalidObjectType.system()+": "+TOtMetaInfo::name(castable(stack[0])));
         return false;
         }
      TOtLexem lek;
      TArray_Int ranges(1,0,4);
      if (yes_not) match(TOtLexem::opNot);
      match(TOtLexem::opQuestion); match(lek,TOtLexem::spLeftCramp);
      TOtFuncFinderHolder holder(adventurers); holder.tune(program,iBeg,main(lek));
      TOtFuncProfile& p=holder.p(); TOtFuncFinder& finder=holder.finder();
      finder.param(type_in,codes.last());
      bool yes_Num=castable(type_r,TOtType::RNum), yes_Int=castable(type_r,TOtType::RInt),yes_Ptr=castable(type_r,TOtType::RPtr);
      int index=0;
      do {
         if (! notVoidExpression() ) return false;
         if (!castable(stack[0],type_r) && (stack[0]!=TOtType__Null)) {
            if (yes_Num && castable(stack[0],TOtType__RInt)) {
               TOtProgram::TToken t; t.type=TOtProgram::TToken::operStack; t.id=0; t.oper=-cast_Int2Num;
               codeAdd(t); stack[0]=TOtType__RNum;
               }
            else if (yes_Int && castable(stack[0],TOtType__RNum)) {
               TOtProgram::TToken t; t.type=TOtProgram::TToken::operStack; t.id=0; t.oper=-cast_Num2Int;
               codeAdd(t); stack[0]=TOtType__RInt;
               }
            else {
               error(lexMess_ObjectTypesMismatch.system()+" "+TOtMetaInfo::name(castable(stack[0]))+" : "+TOtMetaInfo::name(castable(type_r)));
               return false;
               }
            }
         index++;
         finder.param(stack[0],codes.last());
         if (!yes_Ptr && match(TOtLexem::spEllipsis)) {
            TOtLexem lek_(xel);
            ranges.add(index);
            if (! notVoidExpression() ) return false;
            if ((stack[-1]==TOtType__Null) || (stack[0]==TOtType__Null)) {
               error(lexMess_ObjectTypesMismatch.system(),lek_);
               return false;
               }
            else if (!castable(stack[0],type_r)) {
               if (yes_Num && castable(stack[0],TOtType::RInt)) {
                  TOtProgram::TToken t; t.type=TOtProgram::TToken::operStack; t.id=0; t.oper=-cast_Int2Num;
                  codeAdd(t); stack[0]=TOtType::RNum;
                  }
               else if (yes_Int && castable(stack[0],TOtType::RNum)) {
                  TOtProgram::TToken t; t.type=TOtProgram::TToken::operStack; t.id=0; t.oper=-cast_Num2Int;
                  codeAdd(t); stack[0]=TOtType::RInt;
                  }
               else {
                  error(lexMess_ObjectTypesMismatch.system()+" "+TOtMetaInfo::name(castable(stack[0]))+" : "+TOtMetaInfo::name(castable(type_r)));
                  return false;
                  }
               }
            index++;
            finder.param(stack[0],codes.last());
            }
      } while ( match(TOtLexem::spComma) );

      if (!needBracket(TOtLexem::spRightCramp,'}')) return false;
      int range=ranges.count();
      for (int i=ranges.low(); i<=ranges.last(); i++) {
         genPushInt(TInt(ranges[i]),mdgpiNone);
         finder.param(stack[0],codes.last());
         }
      if (!yes_Ptr) {
         genPushInt(TInt(range),mdgpiNone);
         finder.param(stack[0],codes.last());
         }
      if (yes_not) p.name("@?_not@"); else p.name("@?@");
      if (!findAndGenSimpleOrFunc(finder)) {
         error(lexMess_InvalidOperator.system()+" ?",lek); return false;
         }
      }
   return true;
}

int  TOtTranslator::level12(int lvmd)    // !,~,-,+,*,++,--,& level12, level13++, level13--
{
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   TOtLexem lek;
   int lvmd_ret=lvmdTrue;
   if ( match(lek,TOtLexem::opNot) ) {
      if (exceeding()) return false;
      if (! level12() ) return false;
      nesting--;
      if (trueChain.yesGoTo() || falseChain.yesGoTo()) {
         trueChain.exchange(falseChain);
         TREE_TRANSVECTION(trUnaryOper,lek,1)
         return true;
         }
      if (!isUnary(bpOld) || !prefixOperator(iBeg)) return false;
      TREE_TRANSVECTION(trUnaryOper,lek,1)
      return genNot();
      }
   if ( match(lek,TOtLexem::opTilda) || match(lek,TOtLexem::opSub) || match(lek, TOtLexem::opAdd)) {
      if (exceeding()) return false;
      if (! level12() ) return false;
      nesting--;
      genValue();
      bool ret=isUnary(bpOld) && prefixOperator(iBeg,lek);
      return ret;
      }
   if ( match(lek,TOtLexem::rvNew) ) {
      TREE_MARKER(lek) //  New
      TOtLexem l;
      if (!getIdent(l)) { error(lexMess_NoIdent.system()); return false; }
      TREE_PUSH(trIdent,l)
      TString templateName=getText(l);
      while (match(TOtLexem::spColonColon)) {
         templateName+=getText(xel);
         TOtLexem lek_cc(xel);
         if (!getIdent(l)) { error(lexMess_NoIdent.system()); return false; }
         templateName+=getText(l);
         TREE_PUSH(trIdent,l);
         TREE_TRANSVECTION(trPrecise,lek_cc,2)
         }
      TREE_LEAVE(trNew)
      if (match(TOtLexem::spLeftBracket)) {
         if (!needBracket(TOtLexem::spRightBracket,')')) return false;
         }
      TOtLexem l_s(l); l_s.group=TOtLexem::glStr; l_s.type=TOtLexem::lkStr;
      l_s.idx=addStrLiter(templateName);
      return newOperator(iBeg,l_s);
      }
   if ( match(lek,TOtLexem::opAddAdd) || match(lek,TOtLexem::opSubSub) ) {
      if (exceeding()) return false;
      if (! level12() ) return false;
      nesting--;
      bool ret=isVariable() && isUnary(bpOld) && prefixOperator(iBeg,lek);
      return ret;
      }
   if ( match(lek,TOtLexem::opMulti) ) {
      if (! level12() ) return false;
      bool ret=isVariable() && isUnary(bpOld) && operatorDereferencing(iBeg,lek);
      if (ret) {TREE_TRANSVECTION(trUnaryOper,lek,1)}
      return ret;
      }
   if ( match(lek,TOtLexem::opAnd) ) {
      lvmd_ret = level12(lvmd | lvmdReferenc); if (!(lvmd_ret & lvmdTrue) ) return lvmdFalse;
      bool ret=isVariable() && isUnary(bpOld) && ((lvmd_ret & lvmdReferenc) || operatorReferencing(lek));
      if (ret) {TREE_TRANSVECTION(trUnaryOper,lek,1)}
      return ret;
      }

   lvmd_ret = level13(lvmd); if (!(lvmd_ret & lvmdTrue) ) return lvmdFalse;

   if ( match(lek,TOtLexem::opAddAdd) || match(lek,TOtLexem::opSubSub) ) {
      bool ret=isVariable() && isUnary(bpOld) && postfixOperator(iBeg,lek);
      return ret;
      }
   return lvmd_ret;
}

#define PRIM_PRIMARY             1
#define PRIM_PROPERTY            PRIM_PRIMARY
#define PRIM_PROPERTY_PROPERTY  -2
#define PRIM_PROPERTY_INDEX      2
#define PRIM_PROPERTY_ARRAY      3
#define PRIM_TEMPLATE_NAME      -4
#define PRIM_TEMPLATE_NAME_GLOB -5
#define PRIM_NOT_WAS            -1
#define PRIM_WAIT_THIS          -1
#define PRIM_THIS                4

int  TOtTranslator::level13(int lvmd)   // primary.func
{
   TOtLexem l;
   int iBeg=codes.last();
   int bpOld=stack.indexOfTop();
   int lvmd_ret=lvmdTrue;
   int prim=primary(l);
   if (!prim) return false;
      //   primary      PRIM_PRIMARY
      // ::property     PRIM_PROPERTY
      // ::property[]   PRIM_PROPERTY_INDEX
   else if (prim==PRIM_PROPERTY_PROPERTY) { // ::property.
      if (!getIdentWithError(l)) return false;
      }
   else if (prim==PRIM_WAIT_THIS || prim==PRIM_THIS) { 
      // this.
      }
   else if (prim==PRIM_TEMPLATE_NAME || prim==PRIM_TEMPLATE_NAME_GLOB) { 
      // TObj::name ,TObj::property  ::TObj::name ,::TObj::property
      }
   TOtLexem curLekProperty;
   while ((prim<0) || match(curLekProperty,TOtLexem::lkProperty)) {

      if (!isUnary(bpOld)) {
         error(lexMess_VoidObject.system()); return false;
         }
      if ((prim>0) && !getIdent(l) && !getPath(l) && !getString(l) && !match(l,TOtLexem::prLPtr) && !match(l,TOtLexem::prLRPtr) && !match(l,TOtLexem::ctTHIS)) {
         error(lexMess_NoIdent.system()); return false;
         }
      if (curLekProperty.subType==TOtLexem::opProperty ) {
         warning_error(lexMess_Obsolete.system(),curLekProperty);
         }

      if (prim>0) {
         if (l.math(TOtLexem::lkIdent) || l.math(TOtLexem::prLPtr) || l.math(TOtLexem::prLRPtr) || l.math(TOtLexem::ctTHIS)) {
            TREE_PUSH(trIdent,l);
            }
         else if (l.math(TOtLexem::lkPath)) {
            TREE_PUSH(trPath,l);
            }
         else {
            if (!castable(stack[0],TOtType::RPtrDocumentNode)) {
               error(lexMess_NoIdent.system()); return false;
               }
            TREE_PUSH(trString,l)       // xxx."XPath"
            }
         }

      if (prim!=PRIM_TEMPLATE_NAME && prim!=PRIM_TEMPLATE_NAME_GLOB && prim!=PRIM_WAIT_THIS) {
         // !(TObj::name ,TObj::property  ::TObj::name ,::TObj::property  <this>)
         TREE_TRANSVECTION(trPrecise,curLekProperty,2)
         }

      TOtFuncFinderHolder holder(adventurers);
      TOtFuncProfile& p=holder.p(); TOtFuncFinder& finder=holder.finder();
      TRelate& rel=finder.relate;
      bool yesAncestor=false;
      if (prim==PRIM_PRIMARY) {
         rel.mode=rltNode;
         }
      else if (prim==PRIM_WAIT_THIS || prim==PRIM_THIS) { 
         // this.
         rel.mode=rltThis;
         rel.index=abs(stack[0].origin);
         }
      else if (prim==PRIM_TEMPLATE_NAME) { 
         rel.mode=rltTemplate;
         rel.index=abs(stack[0].origin);
         }
      else if (prim==PRIM_TEMPLATE_NAME_GLOB) { 
         rel.mode=rltTemplate|rltAncestor;
         rel.index=abs(stack[0].origin);
         }

      if ((prim!=PRIM_TEMPLATE_NAME) && (prim!=PRIM_TEMPLATE_NAME_GLOB) && match(TOtLexem::spColonColon)) {
         // x.TObj::yyyyy
         if (!node) { errorName(lexMess_UnknownIdentify.system(),l); return false; }

         int       sk=TObjectFinder::fmNone,sk_prev=sk;
         bool      yesColonColon=true;
         int       idTemplate=0, idNamespace=0;
         TString   templateName;
         TString   prefix;
         TOtType   templateType;
         TPtrOtDir nsDir;
         TPtrOtDir nsDir_prev;

         int finder_mode =   (TObjectFinder::fmTemplate | TObjectFinder::fmNameSpace |
                              TObjectFinder::fmName     | TObjectFinder::fmOnlyOne   | TObjectFinder::fmTranslate);
         TObjectFinder finder_ns(finder_mode);
         finder_ns.name=getText(l);
         __STATISTIC_ACCUMULATION(67)

         sk=finder_ns.seek(node);
         nsDir=OT_DOWNCAST(finder_ns.obj(),TOtDir);

         TOtLexem  prev;
         while (sk) {
            if (!yesColonColon) { error(lexMess_MissingBracket.system()+" ::",xel); return false; }
            templateName=prefix+finder_ns.name;
            if (sk & TObjectFinder::fmTemplate) {
               if (!findTemplate(finder_ns.name,idTemplate,NULL,nsDir_prev,prefix)) {
                  error(TString(lexMess_CantFindObject.system()) + " : " + templateName);
                  return false;
                  }
               templateType=castable(TOtType(_id_structure,1,-idTemplate));
              }
           else {
              idNamespace = addNamespace(prefix+finder_ns.name,nsDir);
              }

            prefix+=finder_ns.name+scopeSign;

            prev=l;
            TOtLexem lek(xel);
            if (!getIdentWithError(l)) return false;
            TREE_TRANSVECTION(trPrecise,lek,2)

            finder_ns.clear();
            finder_ns.mode = finder_mode;
            finder_ns.name=getText(l);
            sk_prev=sk;
            sk=nsDir->seekInside(finder_ns,TObjectFinder::fmLocal|TObjectFinder::fmWithoutSelf);
            if (sk) {
               yesColonColon=match(TOtLexem::spColonColon);
               nsDir_prev=nsDir;
               nsDir=OT_DOWNCAST(finder_ns.obj(),TOtDir);
               }
            }

         if (sk_prev & (TObjectFinder::fmTemplate | TObjectFinder::fmNameSpace)) {
            rel.templateName=templateName;
            if (sk_prev & TObjectFinder::fmTemplate) {
               // x.TObj::yyyyy
               TOtType type(id_TOtRPtr,1,locStruct[idTemplate].obj->objectType().origin,templateName);
               if (!castable(stack[0],type)) { error(lexMess_ObjectTypesMismatch.system()); return false; }
               rel.index=idTemplate;
               rel.mode=rltTemplate|rltAncestor;
               if (matchNo(TOtLexem::spLeftBracket)) { // x.TObj::func()
                  yesAncestor=true;
                  }
               }
            else if (sk_prev & TObjectFinder::fmNameSpace) {
               // x.NS::yyyyy
               rel.index=idNamespace;
               rel.mode=rltNamespace;
               }
            }
         else {
            error(TString(lexMess_CantFindObject.system()) + " : " + getText(l),l); return false;
            }
         }

      holder.tune(program,((prim == PRIM_TEMPLATE_NAME) || (prim == PRIM_TEMPLATE_NAME_GLOB) || yesAncestor) ? codes.last() : iBeg,main(l));
      if (!yesAncestor) {
         holder.param(stack[0],codes.last());  // pointer
         }
      else {
         stack.pop();
         }

      if (l.math(TOtLexem::lkStr) && castable(stack[0],TOtType::RPtrDocumentNode)) { // xxx."XPath"
         prim=PRIM_PRIMARY;  continue;
         }

      if (l.math(TOtLexem::prLPtr)) {
         if (!cast2prt(0x03)) return false;
         prim=PRIM_PRIMARY;  continue;
         }
      else if (l.math(TOtLexem::prLRPtr)) {
         if (!cast2prt(0x07)) return false;
         prim=PRIM_PRIMARY;  continue;
         }
      else if (getText(l)=="Ptr") {
         if (!cast2prt(0x01)) return false;
         prim=PRIM_PRIMARY;  continue;
         }

      if (match(TOtLexem::spLeftBracket)) { // .func()
         int ret=makecall(finder,l,false);
         if ((ret==PRIM_PRIMARY) && match(TOtLexem::spLeftScrape)) {
            if (!index(iBeg,xel)) return false;
            }
         if (!ret) return false;
         if (ret==PRIM_NOT_WAS) {
            ret=makenew(finder,l);
            if (!ret) return false;
            if (ret==PRIM_NOT_WAS) {
               errorFuncNotFind(finder,l); return false;
               }
            }
         prim=PRIM_PRIMARY;  continue;
         }

      TOtType stack_0=stack[0];
      while ((stack_0.id==_id_array) || (stack_0.id==_id_property)) {
         int ip=stack_0.origin;
         stack_0=property[ip].result();
         }
      if (stack_0.isStructureOblique()) {
         int owner=abs(stack_0.origin);
         const TLocStruct& loc=locStruct[owner];
         if (loc.obj) {
            int prop=loc.obj->findUserProp(getText(l));
            if (prop) {
               if (!userproperty(finder,l,loc.obj,prop)) return false;
               prim=PRIM_PRIMARY;  continue;
               }
            }
         int field=locStruct.find(owner,getText(l));
         if (field) {
            const TLocStruct& loc2=locStruct[field];
            if (loc2.getType() == id_unknown) {
               error(lexMess_ObjectTypesMismatch.system()); return false;
            }
            if (loc2.obj) {
               TString err_text = denial_text(loc2.obj);
               if (err_text != EMPTY_STR) { 
                  stack.pop();
                  int prop=makeproperty(finder,l,getText(l));
                  if (prop) { prim=PRIM_PRIMARY; continue; }
                  error(err_text); return false; 
                  }
               if (loc2.obj->deprecated) { 
                  if (!matchNo(TOtLexem::spLeftScrape)) {
                     TOtType stack_top=stack[0];
                     stack.pop();
                     int prop=makeproperty(finder,l,getText(l),false);
                     if (prop) { prim=PRIM_PRIMARY; continue; }
                     stack.push(stack_top);
                     }
                  warning(lexMess_WarningDeprecated.system()); 
                  }
               }
            if (loc2.isProperty) {
               if (!user_property(finder,l,loc2,field)) return false;
               prim=PRIM_PRIMARY; continue;
               }
            if (!prefixOperator(iBeg) || !genPushFieldStruct(owner,field,l)) return false;
            if (loc2.isRef) {
               if ((lvmd & lvmdReferenc) && !matchNo(TOtLexem::lkProperty)) {
                  lvmd_ret |= lvmdReferenc;
                  }
               else {
                  if (!genDereferencing(-1)) return false;
                  }
               }
            if (match(TOtLexem::spLeftScrape)) {
               if (!index(iBeg,l)) return false;
               }
            prim=PRIM_PRIMARY; continue;
            }
         if (loc.isXML) {
            }
         }

      if (!stack_0.isStructure() && (stack_0.id !=_id_array) && !TOtMetaInfo::castable(stack_0,TOtType(id_TOtRPtr))) {
         if ((curLekProperty.subType==TOtLexem::opPoint) && TOtMetaInfo::castable(stack_0,TOtType(id_TOtRef)) && genRefToPtr()) {
            p.param(p.param.low())=stack[0];
            }
         else {
            error(lexMess_NoPointer.system()); return false;
            }
         }

      if ((prim==PRIM_TEMPLATE_NAME) && !l.math(TOtLexem::ctTHIS)) { // TObj::property
         bool cast=dirTemplate && castable(TOtType(id_TOtRPtr,1,dirTemplate->objectType().origin,dirTemplate->getTemplateName()),stack[0]);
         if (cast) {
            genPop(false,0);          //  -indexTemplate
            TOtType type=TOtType(_id_structure,1,-indexThis);
            genPushField(type,l);
            }
         }

      stack_0=stack[0];
      if ((stack_0.origin ==id_TOtDocumentNode) && (stack_0.oblique==1) && stack_0.templateName.len()) {
         int ret=yesXMLPath(l);
         if (ret<0) { return false; }
         if (ret)   { prim=PRIM_PRIMARY; continue; }
         }
      stack.pop();

      int prop=makeproperty(finder,l,getText(l));
      if (prop==PRIM_PROPERTY_ARRAY) {
         prop=property2array(finder,l);
         if (prop && match(TOtLexem::spLeftScrape)) {
            return index(iBeg,l);
            }
         }
      if (!prop) { return false; }
      prim=PRIM_PRIMARY;
      }
   return lvmd_ret;
}
int  TOtTranslator::primary(TOtLexem& l)   //  var, constant
{
   int iBeg=codes.last();
   if (match(TOtLexem::spLeftBracket)) {
      bool yes_ptr=true;
#ifdef CONFORMANCE
      OnRestitution(); 
      if (match(TOtLexem::lkIdent)) {
         while (yes_ptr && match(TOtLexem::spColonColon)) {
            if (!match(TOtLexem::lkIdent)) yes_ptr=false;
            }
         while (yes_ptr && match(TOtLexem::opPoint)) {
            if (!(match(TOtLexem::lkIdent) || match(TOtLexem::lkPath))) yes_ptr=false;
            }
         if (match(TOtLexem::opMulti)) {
            while (match(TOtLexem::opMulti));
            if (!match(TOtLexem::spRightBracket)) yes_ptr=false;
            }
         else {
            yes_ptr=false;
            }
         }
      else {
         yes_ptr=false;
         }
      OffRestitution(); 
#else
      yes_ptr=false;
#endif
      if (yes_ptr) {
         // (Tttt*)
         return cast2prt(0x08);
         }
      else {
         TREE_MARKER(xel)  //  Primary
         trueChain .push();
         falseChain.push();
         if (TTask::currTask()->freeStackSpace() < _MINIMUM_SUPPLY_STACK_) {
            error(lexMess_WarningCycling.system()); return false;
            }
         if (! level1() ) return false;
         falseChain.merge();
         trueChain .merge();
         if (!needBracket(TOtLexem::spRightBracket,')')) return false;
         TREE_LEAVE(trPrimary)
         if (match(TOtLexem::spLeftScrape)) {
            if (!index(iBeg,xel)) return false;
            }
         return PRIM_PRIMARY;
         }
      }

   int id;
   if (getIdent(l)) {
      TREE_PUSH(trIdent,l)
      if (match(TOtLexem::spLeftBracket)) {
         //  func()
         TOtFuncFinderHolder holder(adventurers); holder.tune(program,iBeg,main(l));
         TOtFuncProfile& p=holder.p(); TOtFuncFinder& finder=holder.finder();
         int ret=makecall(finder,l,false);
         if ((ret==PRIM_PRIMARY) && match(TOtLexem::spLeftScrape)) {
            if (!index(iBeg,xel)) return false;
            }
         if (ret!=PRIM_NOT_WAS) return ret;
         ret=makenew(finder,l);
         if (ret!=PRIM_NOT_WAS) return ret;
         if ((p.param.count() == 1) && (TOtMetaInfo::castable(p.param[p.param.low()],TOtType(id_TOtRPtr))) ) {
            TOtType type;
            TString name=p.name();
            if ((name.len()>3) && (!name.compare("Ptr",3))) {
               TString title("RPtr@"+name.remove(0,3));
               type=node?node->metaType(title):TOtMetaInfo::type(title);
               }
            if (type.origin!=id_unknown) {
               warning(lexMess_Obsolete.system());
               genPushInt(TInt(type.origin));
               p.name("CastToPtr");
               holder.param(stack[0],codes.last());
               if (findAndGenSimpleOrFunc(finder)) {
                  stack[0]=type;
                  return PRIM_PRIMARY;
                  }
               }
            }
         errorFuncNotFind(finder,l);
         return false;
         }
      else if (!matchNo(TOtLexem::spColonColon) && ((id=varIndex(getText(l))) != 0)) {
         // var
         if ((id<0) && (locVar[-id].state&TLocVar::svDefinite)) {
            TString mess=getText(l); mess << " - "; mess << lexMess_NotInitialized.system();
            warning_error(mess,l,TOtTranslateMessage::tWarning);
            }
         TOtType tv(getVarObjectType(id));
         if (endPos) setLastObject(id);
         if (tv.id==_id_local_array || tv.id==_id_pointer_array) {
            if (match(TOtLexem::lkProperty)) {
               TOtLexem count;
               if (!getIdentWithError(count)) return false;
               if (getText(count) != "ItemCount") {
                  errorName(lexMess_UnknownIdentify.system(),count); return false;
                  }
               genPushInt(TInt(locVar[-id].size));
               return PRIM_PRIMARY;
               }
            if (!needBracket(TOtLexem::spLeftScrape,'[')) return false;
            TREE_MARKER(xel)  //   List
            if (! notVoidExpression() ) return false;
            if (!prefixExpressionOperator(iBeg)) return false;
            if (!TOtMetaInfo::castable(stack[0],TOtType::RInt)) {
               error(lexMess_NoIntType.system()); return false;
               }
            genPushArr(id,l);
            if (!needBracket(TOtLexem::spRightScrape,']')) return false;
            TREE_LEAVE(trList)
            TREE_TRANSVECTION(trItem,xel,2)
            }
         else {
            genPushVar(id,l,mdgpvStruct);
            if (match(TOtLexem::spLeftScrape)) {
               return index(iBeg,l);
               }
            }
         return PRIM_PRIMARY;
         }
      else if (getText(l)=="Ptr") {
         // Ptr@Tttt()
         return cast2prt(0x00);
         }
      else {
         if (match(TOtLexem::spColonColon)) {
            // Ident::
            TString text=getText(l);
            int e=abs(locStruct.findEnum(text,EMPTY_STR));
            if (e) {
               // TEnum::
               TOtLexem lek(xel);
               if (!getIdentWithError(l)) return false;
               TREE_TRANSVECTION(trPrecise,lek,2)
               e=abs(locStruct.findEnum(text,getText(l)));
               if (!e) { errorName(lexMess_UnknownIdentify.system(),l); return false; }
               l.inm=locStruct[e].link;
               genPushInt(l);
               return PRIM_PRIMARY; // TEnum::enum
               }

            if (!node) { errorName(lexMess_UnknownIdentify.system(),l); return false; }

            int       sk=TObjectFinder::fmNone,sk_prev=sk;
            bool      yesColonColon=true;
            int       idTemplate=0, idNamespace=0;
            TString   templateName;
            TString   prefix,key;
            TOtType   templateType;
            TPtrOtDir nsDir,nsDir_prev;

            int finder_mode =   (TObjectFinder::fmTemplate | TObjectFinder::fmConst   | TObjectFinder::fmMeet   | TObjectFinder::fmNameSpace | TObjectFinder::fmConstOwner | //TObjectFinder::fmDocument |
                                 TObjectFinder::fmName     | TObjectFinder::fmOnlyOne | TObjectFinder::fmTranslate);
            TObjectFinder finder(finder_mode);
            finder.name=getText(l);
            finder.setContext(node);
            __STATISTIC_ACCUMULATION(67)

            TNameFinderBuffer::TNameItem item;
            item.mode=finder.mode & finder.fmSpecifically;
            if (names.findName(item,finder.name)) {
               sk=item.ret;
               finder.ptr=item.ptr;
               nsDir=OT_DOWNCAST(item.ptr,TOtDir);
               if (endPos) setLastObject(finder.ptr);
               }
            else {
               sk=finder.seek(node);
               if (sk) {
                  item.ptr=finder.obj();
                  item.ret=sk;
                  item.name=finder.name;
                  names.addName(item);
                  if (endPos) setLastObject(item.ptr);
                  }
               nsDir=OT_DOWNCAST(finder.obj(),TOtDir);
               }

            TOtLexem  prev;
            while ((sk & (TObjectFinder::fmTemplate | TObjectFinder::fmNameSpace)) && yesColonColon) {
//               if (!yesColonColon) { error(lexMess_MissingBracket.system()+" ::",xel); return false; }
               templateName=prefix+finder.name;
               if (sk & TObjectFinder::fmTemplate) {
                  if (!findTemplate(finder.name,idTemplate,NULL,nsDir_prev,prefix)) {
                     error(TString(lexMess_CantFindObject.system()) + " : " + templateName);
                     return false;
                     }
                  templateType=castable(TOtType(_id_structure,1,-idTemplate));
                  key=finder.name+scopeSign;
                  }
               else {
                  idNamespace = addNamespace(prefix+finder.name,nsDir);
                  key="";
                  }

               prefix+=finder.name+scopeSign;

               prev=l;
               TOtLexem lek(xel);
               if (match(l,TOtLexem::ctTHIS)) {
                  TREE_PUSH(trIdent,l)
                  }
               else {
                  if (!getIdentWithError(l)) return false;
                  }
               TREE_TRANSVECTION(trPrecise,lek,2)

               finder.clear();
               finder.mode = finder_mode;
               finder.name=getText(l);
               sk_prev=sk;
               if (matchNo(TOtLexem::spLeftBracket) || matchNo(TOtLexem::spLeftScrape)) {
                  sk=TObjectFinder::fmNone; // TObj::func(), TObj::arr[]
                  break;
                  }
               sk=nsDir->seekInside(finder,TObjectFinder::fmLocal|TObjectFinder::fmWithoutSelf);
               if (sk) yesColonColon=match(TOtLexem::spColonColon);
               if (sk & (TObjectFinder::fmTemplate | TObjectFinder::fmNameSpace | TObjectFinder::fmConstOwner)) {
                  nsDir_prev=nsDir;
                  nsDir=OT_DOWNCAST(finder.obj(),TOtDir);
                  if (endPos) setLastObject(nsDir);
                  }
               }

            if (sk & TObjectFinder::fmConstOwner) {
               if (yesColonColon) {
                  key=finder.name+scopeSign;

                  TOtLexem lek(xel);
                  if (match(l,TOtLexem::ctTHIS)) {
                     TREE_PUSH(trIdent,l)
                     }
                  else {
                     if (!getIdentWithError(l)) return false;
                     }
                  TREE_TRANSVECTION(trPrecise,lek,2)

                  finder.clear();
                  finder.name=getText(l);
                  sk_prev=sk;
                  finder.mode=TObjectFinder::fmConst | TObjectFinder::fmMeet | TObjectFinder::fmName | TObjectFinder::fmOnlyOne | TObjectFinder::fmTranslate;
                  sk=nsDir->seekInside(finder,TObjectFinder::fmLocal);
                  if (sk) yesColonColon=match(TOtLexem::spColonColon);
                  }
               }

            if (sk & (TObjectFinder::fmConst | TObjectFinder::fmMeet)) {
               if (yesColonColon) {
                  sk_prev=sk;
                  prev=l;
                  TOtLexem lek(xel);
                  if (match(l,TOtLexem::ctTHIS)) {
                     TREE_PUSH(trIdent,l)
                     }
                  else {
                     if (!getIdentWithError(l)) return false;
                     }
                  TREE_TRANSVECTION(trPrecise,lek,2)
                  key+=finder.name+scopeSign;
                  }
               else {
                  genPushFieldSeek(finder.obj()->objectType(),prefix+finder.name,l);
                  return PRIM_PRIMARY;
                  }
               }

            if (sk & TObjectFinder::fmTemplate) { // !yesColonColon
               TOtType type(finder.obj()->objectType());
               type.templateName=prefix+finder.name;
               genPushFieldSeek(type,prefix+finder.name,l);
               return PRIM_PRIMARY;
               }

            if (match(TOtLexem::spLeftBracket)) {
               TOtFuncFinderHolder holder(adventurers);
               TOtFuncFinder& funcer=holder.finder();
               if (sk_prev & (TObjectFinder::fmTemplate | TObjectFinder::fmNameSpace)) {
                  TRelate& rel=funcer.relate;
                  rel.templateName=templateName;
                  if (sk_prev & TObjectFinder::fmTemplate) {
                     // TObj::func()
                     rel.index=idTemplate;
                     rel.mode=rltTemplate;
                     TOtType type(_id_structure,1,-idTemplate);
                     bool cast=dirTemplate && (dirTemplate->templateCastable(nsDir)>=0);
                     if (cast) { 
                        type.origin=-indexThis; 
                        }
                     else if (dirTemplate && (dirTemplate->getStatus() < TOtObject::stInited)) { 
                        warning_error(TString(lexMess_InvalidObjectStatus.system() + " : " + dirTemplate->getFullName()),l); 
                        }
                     genPushField(type,prev);
                     }
                  else if (sk_prev & TObjectFinder::fmNameSpace) {
                     // NS::func()
                     rel.index=idNamespace;
                     rel.mode=rltNamespace;
                     }
                  holder.tune(program,codes.last(),main(l));
                  }
               else if (sk_prev & (TObjectFinder::fmConst | TObjectFinder::fmMeet)) {
                  // Const::func()
                  holder.tune(program,codes.last(),main(l));
                  genPushFieldSeek(finder.obj()->objectType(),prefix+finder.name,prev);
                  holder.param(stack[0],codes.last());
                  }
               else {
                  errorName(lexMess_UnknownIdentify.system(),l);
                  return false;
                  }
               int ret=makecall(funcer,l);
               if ((ret==PRIM_PRIMARY) && match(TOtLexem::spLeftScrape)) {
                  if (!index(iBeg,xel)) return false;
                  }
               return ret;
               }

            if (yesColonColon && !(sk_prev & TObjectFinder::fmMeet) && (sk_prev & (TObjectFinder::fmTemplate | TObjectFinder::fmConst | TObjectFinder::fmNameSpace | TObjectFinder::fmConstOwner))) {
               // [NS::,TObj::][Dir::][Const::]key
               bool inside_template = nsDir && nsDir->getIsTemplateDefinition();
               TGenConstRet c=genConst(key+getText(l),l,templateType,inside_template?"":prefix,nsDir);
               if (c==gcrYes) {
                  return PRIM_PRIMARY;
                  }
               if (c==gcrError) return false;
               }

            if (sk_prev & TObjectFinder::fmMeet) {
               // Meet::key
               T_Ptr<TOtObjectMeet> meet = OT_DOWNCAST(finder.obj(),TOtObjectMeet);
               if (meet) {
                  TString key_str = getText(l);
                  int index = meet->findKey(key_str);
                  if (index) {
                     const TOtObjectMeet::TItem& meet_item = (*meet)[index]; 
                     genPushFieldSeek(meet_item.type,key+key_str,prev);
                     if (!(meet_item.mode & meet_item.imNoReference) && 
                         (TOtMetaInfo::castable(meet_item.type,id_TOtValue) ||
                          TOtMetaInfo::castable(meet_item.type,id_TOtObjectPtr))) {
                        if (!genDereferencing(-1)) return false;
                        }
                     return PRIM_PRIMARY;
                     }
                  }
               }

            if (sk_prev & TObjectFinder::fmTemplate) {
               // TObj::name ,TObj::prop
               TOtType type=TOtType(_id_structure,1,-idTemplate);
               genPushField(type,prev);
               stack.push(type);
               return PRIM_TEMPLATE_NAME;
               }

            if (sk_prev & (TObjectFinder::fmConst | TObjectFinder::fmMeet)) {
               // Const::prop
               TOtFuncFinderHolder holder(adventurers); holder.tune(program,codes.last(),main(l));
               TOtFuncFinder& funcer=holder.finder();
               genPushFieldSeek(finder.obj()->objectType(),prefix+finder.name,prev);
               holder.param(stack[0],codes.last());
               stack.pop();
               return makeproperty(funcer,l,getText(l));
               }

            errorName(lexMess_UnknownIdentify.system(),l);
            return false;
            }
         else {
            // Ident !::
            TString text=getText(l);
            int e=abs(locStruct.findEnum(EMPTY_STR,text));
            if (e) {
               // enum
               l.inm=locStruct[e].link;
               genPushInt(l);
               return PRIM_PRIMARY;
               }
            // label:
            if ((getLanguage() & lkYesGoTo) && match(TOtLexem::spColon)) {
               TREE_TRANSVECTION(trLabel,l,1)
               if (!genLabel(l)) { error(lexMess_DoubleName.system(),l); return false; }
               return PRIM_PRIMARY;
               }

            TGenConstRet c=genConst(text,l,TOtType(),"",NULL);  // key
            if (c==gcrYes) return PRIM_PRIMARY;
            if (c==gcrError) return false;

            if (indexThis) { // [this.]
               TOtType type=TOtType(_id_structure,1,-indexThis);
               genPushField(type,l);
               stack.push(type);
               return PRIM_WAIT_THIS;
               }

            errorName(lexMess_UnknownIdentify.system(),l);
            return false;
            }
         }
      }

   if (getNumber(l)) {
      genPushNum(l);
      TREE_PUSH(trNum,l)
      return PRIM_PRIMARY;
      }
   if (getInteger(l)) {
      genPushInt(l);
      TREE_PUSH(trInt,l)
      return PRIM_PRIMARY;
      }
   if (getString(l)) {
      genPushStr(l);
      TREE_PUSH(trString,l)
      return PRIM_PRIMARY;
      }
   if (getPath(l)) {
      TREE_PUSH(trPath,l)
      if (!genPushPath(l)) return false;
      if (match(TOtLexem::spLeftScrape)) {
         return index(iBeg,l);
         }
      return PRIM_PRIMARY;
      }
   if (matchNo(TOtLexem::lkConst)) {
      TOtLexem con(lex);
      TREE_PUSH(trIdent,con)
      TOtProgram::TToken t;
      t.type=TOtProgram::TToken::pushPtr;
      if      (match(TOtLexem::ctNULL)) {
         t.type=TOtProgram::TToken::pushNULL;
         t.obj.id=id_void;
         stack.push(TOtType__Null);
         codeAdd(t);
         if (endPos) setLastObject(TOtType__Null);
         return PRIM_PRIMARY;
         }
      else if (match(TOtLexem::ctROOT)) {
         t.obj.id=id_TOtDir;
         stack.push(TOtType(_id_structure,1,-indexROOT));
         if (endPos) setLastObject(TOtNode::root());
         }
      else if (match(TOtLexem::ctTHIS)) {
         t.obj.id=id_TOtProgram;
         t.obj.origin=program->objectTypeId();
         stack.push(TOtType(_id_structure,1,-indexTHIS));
         if (endPos) setLastObject(program);
         }
      else if (match(TOtLexem::ctNODE)) {
         t.obj.id=id_TOtNode;
         TOtNode *owner=program->getOwnerNode();
         if (owner && indexNODE) {
            t.obj.origin= owner->objectTypeId();
            stack.push(TOtType(_id_structure,1,-indexNODE));
            if (endPos) setLastObject(owner);
            }
         else {
            error(lexMess_CantFindObject.system(),con); return false;
            }
         }
      else if (match(TOtLexem::ctThis)) {
         if (!indexThis) {
            error(lexMess_InvalidExpression.system(),con); return false;
            }
         TOtType type=TOtType(_id_structure,1,-indexThis);
         genPushField(type,con);
         stack.push(type);
         if (match(TOtLexem::spLeftScrape)) {
            return index(iBeg,con);
            }
         return PRIM_THIS;
         }

      codeAdd(t);
//      genNone();
      return PRIM_PRIMARY;
      }

   if (match(TOtLexem::spColonColon)) {
      TOtLexem lek(xel);
      TREE_PUSH_TYPE(trNone)
      if (!getIdentWithError(l)) return false;
      TREE_TRANSVECTION(trPrecise,lek,2)
      int idTemplate;
      TOtFuncFinderHolder holder(adventurers);
      TOtFuncFinder& finder=holder.finder();
      TRelate& rel=finder.relate;
      if (findTemplate(getText(l),idTemplate)) {
         if (!match(TOtLexem::spColonColon)) {
            error(TString(lexMess_MissingBracket.system())+" ::"); return false;
            }
         lek=xel;
         TOtLexem func;
         if (!getIdentWithError(func)) return false;
         TREE_TRANSVECTION(trPrecise,lek,2)
         TOtType type=TOtType(_id_structure,1,-idTemplate);
         genPushField(type,l);
         rel.mode=rltTemplate|rltAncestor; 
         rel.index=idTemplate;
         rel.templateName=getText(l);
         if (match(TOtLexem::spLeftBracket)) {
            holder.tune(program,codes.last(),main(func));
            return makecall(finder,func); // ::TObj::func()
            }
         else {
            stack.push(type);
            l=func;
            return PRIM_TEMPLATE_NAME_GLOB; // ::TObj::name ,  ::TObj::prop
            }
         }
      else {  // Global
         rel.mode=rltGlobal;
         holder.tune(program,iBeg,main(l));
         if (match(TOtLexem::spLeftBracket)) return makecall(finder,l);  // ::func()
         return makeproperty(finder,l,getText(l));                       // ::prop
         }
      }

   l=lex;
   if (match(TOtLexem::dfNum)  ||   // num(exp)
       match(TOtLexem::dfInt)  ||
       match(TOtLexem::dfDec)  ||
       match(TOtLexem::dfLong) ||
       match(TOtLexem::dfShort)||
       match(TOtLexem::dfStr)  ||
       match(TOtLexem::dfPtr)  ){
      TOtFuncFinderHolder holder(adventurers); holder.tune(program,iBeg,main(l));
      TOtFuncFinder& finder=holder.finder();
      TREE_PUSH(trIdent,l)
      if (match(TOtLexem::spLeftBracket)) return makecall(finder,l);
      }

   error(lexMess_InvalidExpression.system());
   return false;
}

int  TOtTranslator::makenew(TOtFuncFinder& finder,const TOtLexem& l)
{
   TOtFuncProfile& p=finder.p;
   if ((p.param.count() >= 1) && (p.param.count() <= 2) && (p.name()=="New") &&
       (TOtMetaInfo::castable(p.param[p.param.low()],TOtType(id_TOtLPtr,1,id_TOtObject))) ) {
      TOtType type=castable(p.param[p.param.low()]);
      if (type.oblique!=1) {
         error(TString(lexMess_NewAbstract.system())+" "+TOtMetaInfo::name(type));
         return 0;
         }
      genPushInt(TInt(type.origin));
      p.name("@New@");
      finder.param(stack[0],codes.last());
      if (findAndGenSimpleOrFunc(finder)) {
         TOtType copy=castable(p.param[p.param.low()+1]);
         if ((p.param.count() == 2) || (p.param.count() == 3) && (type.oblique==copy.oblique) &&
             (TOtMetaInfo::castable(TOtType(copy.origin),TOtType(type.origin)))) {
            const TOtMetaInfo::TRec *r=TOtMetaInfo::rec(type.origin);
            if (!r || !r->create) {
               error(TString(lexMess_NewAbstract.system())+" "+TOtMetaInfo::name(TOtType(type.origin)));
               return 0;
               }
            return PRIM_PRIMARY;
            }
         }
      errorFuncNotFind(finder,l); return 0;
      }
   return PRIM_NOT_WAS;
}

#define TITLE_COLON_PARAM
int  TOtTranslator::makecall(TOtFuncFinder& finder,const TOtLexem& l,bool err)
{
   TOtFuncProfile& p=finder.p;
   TREE_MARKER(xel) //  List
   p.name(getText(l));
   if (!match(TOtLexem::spRightBracket)) {
      do {
#ifdef TITLE_COLON_PARAM
         OnRestitution();
         bool yes_title = match(TOtLexem::lkIdent) && match(TOtLexem::spColon);
         OffRestitution();
         if (yes_title) { match(TOtLexem::lkIdent); match(TOtLexem::spColon); }
#endif
         if (! notVoidExpression() ) return 0;
         finder.param(stack[0],codes.last());
      } while ( match(TOtLexem::spComma) );

      if (!needBracket(TOtLexem::spRightBracket,')')) return 0;
      }
   TOtType type;
   if (p.param.count()) type=p.param[p.param.low()];
   int ret=findAndGenSimpleOrFunc(finder);
   if (!ret) {
      if (errCount) return 0;
      if (err) {
         errorFuncNotFind(finder,l); return 0;
         }
      else {
         TREE_LEAVE(trList)
         return PRIM_NOT_WAS;
         }
      }
   int mode=mpResult;
   ret=makeresult(finder,l,mode,type,ret);
   if (!ret) return 0;

   TREE_LEAVE(trList)
   TREE_TRANSVECTION(trCall,xel,2)
   if (endPos && (p.result()!=id_void)) setLastObject(p.result());
   return PRIM_PRIMARY;
}


bool TOtTranslator::cast2prt(int mode) // 0x01 - postfix, 0x02 - LPtr, 0x04 - LRPtr, 0x08 - (castable*)
{
   bool postfix=(mode & 0x01), lptr=(mode & 0x02), multi=(mode & 0x08);
   int iBeg=codes.last();
   TOtType type;
   TOtType v=lptr?TOtType::LRPtr:TOtType::RPtr;

   TOtLexem l; int form=ooNone; 
   bool yes_document=false;
   if (!multi) {
      TString title=lptr?"LRPtr":"RPtr";
      if (!getObliqueOrigin(l,title,v,form)) return false;
      if (form & ooStruct) {
         if (form & ooPrecise) {
            v.id=id_TOtRPtr;
            v.origin=id_TOtDocumentNode;
            yes_document=true;
            }
         type=castable(v);
         }
      else {
         type=v;
         }
      TREE_TRANSVECTION(trType,l,v.oblique+2)
      if (!needBracket(TOtLexem::spLeftBracket,'(') || (!postfix && !notVoidExpression()) || !needBracket(TOtLexem::spRightBracket,')')) return false;
   
      TREE_TRANSVECTION(trList,xel,1)
      TREE_TRANSVECTION(trCall,xel,2)

      }
   else {
      if (!getIdentWithError(l)) return false;
      v=TOtMetaInfo::type(getText(l));
      if (v.id==id_unknown) {
         TString title("RPtr$"); form|=ooTemplate;
         size_t len_pref=title.len();
         title+=getText(l);
         if (!getPrecise(l,title,len_pref,v,form)) return false;
         if (form & ooPrecise) {
            v.id=id_TOtRPtr; v.origin=id_TOtDocumentNode;
            yes_document=true;
            }
         type=castable(v);
         }
      else if (TOtMetaInfo::castable(v.id,id_TOtObject)
#ifdef FLORA_POINTER_OF_VOID
         || (v.id==id_void)
#endif
         ) {
         v.id=id_TOtRPtr; v.oblique=1;
         type=v;
         }
      else {
         error(lexMess_InvalidObjectType.system()+" "+TOtMetaInfo::name(castable(v)),l); return false;
         }
      if (!needBracket(TOtLexem::opMulti,'*')) return false;
      while (match(TOtLexem::opMulti)) v.oblique++;
      if (!needBracket(TOtLexem::spRightBracket,')')) return false;
      if (!level13()) return false;
      }

   static TOtType dir_type(id_TOtRPtr,1,id_TOtDir);
   TOtType w=castable(stack[0]); w.id=type.id;
   if ((type.origin != id_TOtObject) && (type.origin != id_void)) {
      if (castable(w,type)) {
         if (((form & ooTemplate) || !(form & ooStruct)) && (type != dir_type)) {
            warning_error(TString(lexMess_UnnecessaryOperation.system()) + " : " + getText(l),l);
            }
         }
      else if (!castable(type,w)) {
         bool cast = false;
         if (!(form & ooTemplate) && (w.origin != id_TOtDocumentNode) && (w.origin != id_TOtDocumentList)) {
            // Common descendant(derived)
            const TOtMetaInfo::TRec *rec=TOtMetaInfo::rec(w.origin);
            if (rec) for (int i=rec->lstInherit.low();i<=rec->lstInherit.last();i++) {
               const TOtMetaInfo__TInheritanceRec &rr=rec->lstInherit[i];
               if (rr.depth>0) continue;   // ancestor
               const TOtMetaInfo::TRec *rec_derived=TOtMetaInfo::rec(rr.id);
               int i_d;
               if (rec_derived->lstInherit.findKey(&type.origin,i_d)) {
                  const TOtMetaInfo__TInheritanceRec &rr_d=rec_derived->lstInherit[i_d];
                  if (rr_d.depth>=0) { cast = true; break; }  // ancestor
                  }
               }
            }
         if (!cast) {
            error(TString(lexMess_ObjectTypesMismatch.system()) + " : " + TOtMetaInfo::name(type) + " <-> " + TOtMetaInfo::name(w),l);
            }
         }
      }

   TOtFuncFinderHolder holder(adventurers); holder.tune(program,iBeg,main(l));
   TOtFuncProfile& p=holder.p(); TOtFuncFinder& finder=holder.finder();
   holder.param(stack[0],codes.last());
   if (form & ooTemplate) {
      TOtProgram::TToken t;
      t.type=TOtProgram::TToken::pushPtr;
      t.obj.id=id_TOtNode;
      TOtNode *owner=program->getOwnerNode();
      if (owner) {
         short id=owner->objectTypeId();
         t.obj.origin=id;
         stack.push(TOtType(id_TOtRPtr,1,id));
         }
      else {
         error(lexMess_CantFindObject.system(),l); return false;
         }
      codeAdd(t);
      holder.param(stack[0],codes.last());

      if (yes_document) {
         l.group=TOtLexem::glStr; l.type=TOtLexem::lkStr;
         l.idx=addStrLiter(v.templateName);
         genPushStr(l);
         }
      else {
         genPushField(v,l);
         stack.push(v);
         }
      }
   else {
      genPushInt(TInt(type.origin));
      }
   holder.param(stack[0],codes.last());
   p.name(lptr?"CastToLRPtr":"CastToPtr");
   if (!findAndGenSimpleOrFunc(finder)) {
      errorFuncNotFind(finder,l); return false;
      }
   if ((form & ooPrecise) && (stack[0].origin!=id_TOtDocumentNode)) {
      error(TString(lexMess_InvalidObjectType.system()) + " : " + getText(l),l); return false;
      }
   stack[0]=v;
   if (match(TOtLexem::spLeftScrape)) {
      return index(iBeg,l);
      }
   if (endPos) setLastObject(v);
   return true;
}

bool TOtTranslator::userproperty(TOtFuncFinder& finder,TOtLexem& l,TOtObject *obj,int prop)
{
   TOtFuncProfile& p=finder.p;
   int pt=obj->getUserPropType(prop); //user property type
   if (obj->getUserPropDeprecated(prop)) { warning(lexMess_WarningDeprecated.system()); }
   TOtProgram::TUserProperty u;
   u.prop.type=pt;
   u.prop.name=getText(l);
   bool simple=false,rec=false, yes_ptr=false,arr=false,point=false;
   bool in_foreach=(blocks.blocks[0].type==TOtlBlock::blForeach) && (stack.indexOfTop()==2);
   T_Array<TOtType,TArray::aoMemShift> my_stack(0,4,4);

   my_stack.add(stack.top()); stack.pop();
   genPushStr(l);  u.prop.index=codes.last();
   finder.param(stack[0],codes.last());
   my_stack.add(stack.top()); stack.pop();

   TString name,prefix("UserProp");
   TOtType type; int idTemplate;  // ptPtr
   switch (pt) {
      case TUserData::ptNum :
         name+="Num";   type=TOtType::LRNum;    simple=true;
         break;
      case TUserData::ptInt :
         name+="Int";   type=TOtType::LRInt;    simple=true;
         break;
      case TUserData::ptStr :
         name+="Str";   type=TOtType::LRStr;    simple=true;
         break;
      case TUserData::ptPtr :
         name+="Ptr";       simple=true;        yes_ptr=true;
         obj->getUserPropPtrType(prop,type);
         type.id=id_TOtLRPtr;
         if (type.templateName.len()) {
            if (!findTemplateWithError(type.templateName,idTemplate,l)) { return false; }
            type.origin=idTemplate;
            type.id=_id_structure;
            }
         break;
      case TUserData::ptArrNum :
         name+="Num";   type=TOtType::LRNum;    arr=true;
         break;
      case TUserData::ptArrInt :
         name+="Int";   type=TOtType::LRInt;    arr=true;
         break;
      case TUserData::ptArrStr :
         name+="Str";   type=TOtType::LRStr;    arr=true;
         break;
      case TUserData::ptArrPtr : {
         name+="Ptr";       arr=true;          yes_ptr=true;
         TOtPtrValueArray *a=obj->getUserPropArrPtr(prop);
         type = a->getPointerType();
         if (type.templateName.len()) {
            if (!findTemplateWithError(type.templateName,idTemplate,l)) { return false; }
            type.origin=idTemplate;
            type.id=_id_structure;
            }
         } break;
      case TUserData::ptArrRec : {
         if (matchNo(TOtLexem::spLeftScrape)) {
            TREE_MARKER(lex) //  List
            if (!needBracket(TOtLexem::spLeftScrape,'[') ||
                !notVoidExpression() ||
                !needBracket(TOtLexem::spRightScrape,']') ||
                !needBracket(TOtLexem::opPoint,'.')) return false;
            finder.param(stack[0],codes.last());
            my_stack.add(stack.top()); stack.pop();
            TREE_LEAVE(trList)
            TREE_TRANSVECTION(trItem,xel,2)
            }
         else {
            if (in_foreach && (matchNo(TOtLexem::spComma) || matchNo(TOtLexem::spSemiColon) || matchNo(TOtLexem::spRightBracket))) {
               program->props.add(u);
               int find=program->props.last();
               TProperty pr; pr.user=true; pr.fget=find; pr.fset=find; pr.result(my_stack[my_stack.low()]);
               property.add(pr);
               TOtType type_(_id_property,1,-property.last());
               stack.push(type_);
               return true;
               }
            if (!needBracket(TOtLexem::opPoint,'.')) return false;
            arr=true; point=true;
            }
         TOtLexem lek(xel);
         if (endPos) { setLastObject(type); lastObject.obj=(TOtObject*)obj; setLastObject(u); }
         if (!getIdentWithError(l)) return false;
         TREE_TRANSVECTION(trPrecise,lek,2)
         int field;
         if (obj->findUserPropField(prop,getText(l),field) && field) {
            prefix+="Field";

            genPushStr(l);  u.field.index=codes.last();
            finder.param(stack[0],codes.last());
            my_stack.add(stack.top()); stack.pop();

            int rt;
            if (!obj->getUserPropFieldType(prop,field,rt)) {
               error(lexMess_UnknownObjectType.system(),l);
               return false;
               }
            u.field.type=rt;
            u.field.name=getText(l);
            switch (rt) {
               case TUserData::ptNum :
                  name+="Num"; type=TOtType::LRNum;
                  break;
               case TUserData::ptInt :
                  name+="Int"; type=TOtType::LRInt;
                  break;
               case TUserData::ptStr :
                  name+="Str"; type=TOtType::LRStr;
                  break;
               case TUserData::ptPtr : {
                  name+="Ptr";       yes_ptr=true;
                  TOtPtrValueArray *a=obj->getUserPropFieldArrPtr(prop,field);
                  type = a->getPointerType();
                  if (type.templateName.len()) {
                     if (!findTemplateWithError(type.templateName,idTemplate,l)) { return false; }
                     type.origin=idTemplate;
                     type.id=_id_structure;
                     }
                  } break;
               default:break;
               }
            rec=true;
            }
         } break;
      default:break;
      }
   finder.relate.mode=rltNode;
   if (simple) {
      prefix+=name;
/*
      if (match(l,TOtLexem::opPoint)) {
         if (!getIdentWithError(l)) return false;
         prefix+=getText(l);
         return makeproperty(p,c,l,prefix);
         }
*/
      int ret=makeuserprop(u,finder,l);
      if (!ret) return false;
      if (ret==PRIM_PROPERTY_INDEX) { error(lexMess_InvalidIndexProperty.system(),l); return false; }
      if (yes_ptr) {
         if (ret==PRIM_PROPERTY_PROPERTY)
            stack[0]=type;
         else
            property[stack[0].origin].result(type);
         }
      if (endPos) setLastObject(type);
      return true;
      }
   else if (arr) {
      if (matchNo(TOtLexem::spLeftScrape)) {
         prefix+=name;
         int ret=makeuserprop(u,finder,l);
         if (!ret) return false;
         if (yes_ptr) {
            if (ret==PRIM_PROPERTY_PROPERTY)
               stack[0]=type;
            else
               property[stack[0].origin].result(type);
            }
         if (endPos) setLastObject(type);
         }
      else if (point && !rec || match(l,TOtLexem::opPoint)) {
         if (!point && !getIdent(l)) {
            error(lexMess_NoIdent.system()); return false;
            }
         TString pure=prefix;
         if (point && rec) {
            if (!getIdentWithError(l)) return false;
            prefix+=name;
            }
         if (match(TOtLexem::spLeftBracket)) {
            TREE_MARKER(xel) //  List
            for (int i=my_stack.low();i<=my_stack.last();i++) {
               stack.push(my_stack[i]);
               }
            TString func=getText(l);
            if (!match(TOtLexem::spRightBracket)) {
               do {
                  if (! notVoidExpression() ) return false;
                  finder.param(stack[0],codes.last());
                  }
               while ( match(TOtLexem::spComma) );
               if (!needBracket(TOtLexem::spRightBracket,')')) return false;
               }
            TREE_LEAVE(trList)
            TREE_TRANSVECTION(trCall,xel,2)
            prefix+=func; p.name(prefix);
            bool err=!findAndGenSimpleOrFunc(finder);
            if (err && name.len()) {
               p.name(pure+func+name);
               err=!findAndGenSimpleOrFunc(finder);
               }
            if (err) {
               p.name(pure+func);
               err=!findAndGenSimpleOrFunc(finder);
               }
            if (err) {
               errorName(lexMess_UnknownIdentify.system(),l); return false;
               }
            }
         else {
            prefix+=getText(l);
            return makeproperty(finder,l,prefix);
            }
         }
      else {
         if (in_foreach && (matchNo(TOtLexem::spComma) || matchNo(TOtLexem::spSemiColon) || matchNo(TOtLexem::spRightBracket))) {
            program->props.add(u);
            int find=program->props.last();
            TProperty pr; pr.user=true; pr.fget=find; pr.fset=find;
            pr.result(my_stack[my_stack.low()]); pr.c.result=type;
            property.add(pr);
            TOtType type_(_id_property,1,-property.last());
            stack.push(type_);
            return true;
            }
         prefix+="Arr";
         prefix+=name;
         int ret=makeproperty(finder,l,prefix);
         if (!ret) return false;
         if (ret!=PRIM_PROPERTY) { error(lexMess_InvalidIndexProperty.system(),l); return false; }
         }
      return true;
      }
   else if (rec) {
      prefix+=name;
      int ret=makeuserprop(u,finder,l);
      if (!ret) return false;
      if (yes_ptr) {
         if (ret==PRIM_PROPERTY_PROPERTY)
            stack[0]=type;
         else
            property[stack[0].origin].result(type);
         }
      return true;
      }
   else {
      error(lexMess_UnknownObjectType.system(),l); return false;
      }
}

bool TOtTranslator::user_property(TOtFuncFinder& finder,TOtLexem& l,const TLocStruct& loc,int prop)
{
   TOtFuncProfile& p=finder.p;
   int pt=loc.getType().id; //user property type
   TOtProgram::TUserProperty u;
   u.prop.name=getText(l);
   bool simple=false,rec=false,yes_ptr=false,arr=false,point=false;
   bool in_foreach=(blocks.blocks[0].type==TOtlBlock::blForeach) && (stack.indexOfTop()==2);
   T_Array<TOtType,TArray::aoMemShift> my_stack(0,4,4);

   my_stack.add(stack.top()); stack.pop();
   genPushStr(l);  u.prop.index=codes.last();
   finder.param(stack[0],codes.last());
   my_stack.add(stack.top()); stack.pop();

   TString name,prefix("UserProp");
   TOtType type; int idTemplate;
   switch (pt) {
      case id_TOtNum :
         name+="Num";   type=TOtType::LRNum;    simple=true;
         u.prop.type=TUserData::ptNum;
         break;
      case id_TOtInt :
         name+="Int";   type=TOtType::LRInt;    simple=true;
         u.prop.type=TUserData::ptInt;
         break;
      case id_TOtStr :
         name+="Str";   type=TOtType::LRStr;    simple=true;
         u.prop.type=TUserData::ptStr;
         break;
      case id_TOtPtr :
         name+="Ptr";         simple=true;      yes_ptr=true;
         u.prop.type=TUserData::ptPtr;
         type=loc.getType();
         if (type.templateName.len()) {
            if (!findTemplateWithError(type.templateName,idTemplate,l)) { return false; }
            type.origin=idTemplate;
            type.id=_id_structure;
            }
         break;
      case id_TOtArrNum :
         name+="Num";   type=TOtType::LRNum;    arr=true;
         u.prop.type=TUserData::ptArrNum;
         break;
      case id_TOtArrInt :
         name+="Int";   type=TOtType::LRInt;    arr=true;
         u.prop.type=TUserData::ptArrInt;
         break;
      case id_TOtArrStr :
         name+="Str";   type=TOtType::LRStr;    arr=true;
         u.prop.type=TUserData::ptArrStr;
         break;
      case id_TOtArrPtr :
         name+="Ptr";   type=TOtType::LRPtrObject; arr=true;
         u.prop.type=TUserData::ptArrPtr;
         break;
      case id_TOtArrRec : {
         u.prop.type=TUserData::ptArrRec;
         if (matchNo(TOtLexem::spLeftScrape)) {
           TREE_MARKER(lex) //  List
           if (!needBracket(TOtLexem::spLeftScrape,'[') ||
               !notVoidExpression() ||
               !needBracket(TOtLexem::spRightScrape,']') ||
               !needBracket(TOtLexem::opPoint,'.')) return false;
            finder.param(stack[0],codes.last());
            my_stack.add(stack.top()); stack.pop();
            TREE_LEAVE(trList)
            TREE_TRANSVECTION(trItem,xel,2)
            }
         else {
            if (in_foreach && (matchNo(TOtLexem::spComma) || matchNo(TOtLexem::spSemiColon) || matchNo(TOtLexem::spRightBracket))) {
               program->props.add(u);
               int find=program->props.last();
               TProperty pr; pr.user=true; pr.fget=find; pr.fset=find; pr.result(my_stack[my_stack.low()]);
               property.add(pr);
               TOtType type_(_id_property,1,-property.last());
               stack.push(type_);
               return true;
               }
            if (!needBracket(TOtLexem::opPoint,'.')) return false;
            arr=true; point=true;
            }
         TOtLexem lek(xel);
         if (!getIdentWithError(l)) return false;
         TREE_TRANSVECTION(trPrecise,lek,2)
         int field=locStruct.find(prop,getText(l));
         if (field) {
            prefix+="Field";

            genPushStr(l);  u.field.index=codes.last();
            finder.param(stack[0],codes.last());
            my_stack.add(stack.top()); stack.pop();

            int rt=locStruct[field].getType().id;
            u.field.name=getText(l);
            switch (rt) {
               case id_TOtArrNum :
               case id_TOtRecNum :
                  name+="Num";   type=TOtType::LRNum;
                  u.field.type=TUserData::ptNum;
                  break;
               case id_TOtArrInt :
               case id_TOtRecInt :
                  name+="Int";   type=TOtType::LRInt;
                  u.field.type=TUserData::ptInt;
                  break;
               case id_TOtArrStr :
               case id_TOtRecStr :
                  name+="Str";   type=TOtType::LRStr;
                  u.field.type=TUserData::ptStr;
                  break;
               case id_TOtArrPtr :
               case id_TOtRecPtr :
                  name+="Ptr";   type=TOtType::LRPtrObject;
                  u.field.type=TUserData::ptPtr;
                  break;
               default:break;
               }
            rec=true;
            }
         } break;
      default:break;
      }
   if (simple) {
      prefix+=name;
      int ret=makeproperty(finder,l,prefix);
      if (!ret) return false;
      if (ret==PRIM_PROPERTY_INDEX) { error(lexMess_InvalidIndexProperty.system(),l); return false; }
      if (yes_ptr) {
         if (ret==PRIM_PROPERTY_PROPERTY)
            stack[0]=type;
         else
            property[stack[0].origin].result(type);
         }
      return true;
      }
   else if (arr) {
      if (matchNo(TOtLexem::spLeftScrape)) {
         prefix+=name;
         int ret=makeproperty(finder,l,prefix);
         if (!ret) return false;
         if (yes_ptr) {
            if (ret==PRIM_PROPERTY_PROPERTY)
               stack[0]=type;
            else
               property[stack[0].origin].result(type);
            }
         }
      else if (point && !rec || match(l,TOtLexem::opPoint)) {
         if (!point && !getIdent(l)) {
            error(lexMess_NoIdent.system());
            return false;
            }
         TString pure=prefix;
         if (point && rec) {
            if (!getIdentWithError(l)) return false;
            prefix+=name;
            }
         if (match(TOtLexem::spLeftBracket)) {
            TREE_MARKER(xel) //  List
            for (int i=my_stack.low();i<=my_stack.last();i++) {
               stack.push(my_stack[i]);
               }
            TString func=getText(l);
            if (!match(TOtLexem::spRightBracket)) {
               do {
                  if (! notVoidExpression() ) return false;
                  finder.param(stack[0],codes.last());
                  }
               while (match(TOtLexem::spComma));
               if (!needBracket(TOtLexem::spRightBracket,')')) return false;
               }
            TREE_LEAVE(trList)
            TREE_TRANSVECTION(trCall,xel,2)
            prefix+=func; p.name(prefix);
            bool err=!findAndGenSimpleOrFunc(finder);
            if (err && name.len()) {
               p.name(pure+func+name);
               err=!findAndGenSimpleOrFunc(finder);
               }
            if (err) {
               p.name(pure+func);
               err=!findAndGenSimpleOrFunc(finder);
               }
            if (err) {
               errorName(lexMess_UnknownIdentify.system(),l); return false;
               }
            }
         else {
            prefix+=getText(l);
            return makeproperty(finder,l,prefix);
            }
         }
      else {
         if (in_foreach && (matchNo(TOtLexem::spComma) || matchNo(TOtLexem::spSemiColon) || matchNo(TOtLexem::spRightBracket))) {
            program->props.add(u);
            int find=program->props.last();
            TProperty pr; pr.user=true; pr.fget=find; pr.fset=find;
            pr.result(my_stack[my_stack.low()]); pr.c.result=type;
            property.add(pr);
            TOtType type_(_id_property,1,-property.last());
            stack.push(type_);
            return true;
            }
         prefix+="Arr";
         prefix+=name;
         int ret=makeproperty(finder,l,prefix);
         if (!ret) return false;
         if (ret!=PRIM_PROPERTY) {
            error(lexMess_InvalidIndexProperty.system(),l); return false;
            }
         }
      return true;
      }
   else if (rec) {
      prefix+=name;
      return makeproperty(finder,l,prefix);
      }
   else {
      error(lexMess_UnknownObjectType.system(),l);  return false;
      }
}

int  TOtTranslator::property2array(TOtFuncFinder& finder,const TOtLexem& l)
{
   TOtFuncProfile& p=finder.p; TOtFuncCast& c=finder.c;
   const TRelate& rel=finder.relate;
   TString name(getText(l));
   if (rel.mode&rltTemplate) {
      finder.removeFirst();
      }

   p.name(TOtFuncProfile::lexGet+name);

   reformParams(finder);

   c.lek=l.ofsMain();
   c.end=codes.last();
   c.mode|=c.cmProperty;
   finder.save();
   finder.param(TOtType__RInt,codes.last());

   int mode=mpNotVoid;
   int fget=makepoint(finder,l,mode); // ... -> ... ->
   if (!fget) return 0;

   TProperty pr;
   pr.fget=fget;
   pr.p=p; pr.c=c;
   pr.p.name(name);

   TOtType type(castable(pr.result())), type_array(id_TOtRPtr,1,id_TOtObject);
   if (type.id == id_TOtRInt)
      type_array.origin = id_TOtObjectArrInt;
   else if (type.id == id_TOtRNum)
      type_array.origin = id_TOtObjectArrNum;
   else if (type.id == id_TOtRStr)
      type_array.origin = id_TOtObjectArrStr;
   else if (type.id == id_TOtRPtr)
      type_array.origin = id_TOtObjectArrPtr;
   else {
      error(lexMess_InvalidObjectType.system()); return 0;
      }

   finder.reset(); finder.restore();
   p.result(TOtType__RInt);
   p.name(TOtFuncProfile::lexGet+name+TOtFuncProfile::lexCount);
   pr.fset=findAndAddFuncOrFindSimple(finder);
   if (!pr.fset) {
      const TProgramTable& table=program->table.object();
      const T_Array<TProgramTable::TFuncPtr ,TArray::aoMemShift>& program_func=table.func;
      const TProgramTable::TFuncPtr& f=program_func[fget];
      if (f.mode == f.fncLibrary) {
         for (int i=TOtPropertyList::property.low();i<=TOtPropertyList::property.last();i++) {
            const TOtPropertyList::TRec& rec=TOtPropertyList::property[i];
            if (rec.func[TOtPropertyList::fiGet]==f.func) {
               if ((rec.range==1) && (rec.func[TOtPropertyList::fiCount1]!=NULL)) {
                  p.name(rec.func[TOtPropertyList::fiCount1]->profile().name());
                  pr.fset=findAndAddFuncOrFindSimple(finder);
                  break;
                  }
               }
            }
         }
      }
   if (!pr.fset) {
      errorFuncNotFind(finder,l); return 0;
      }
   TOtProgram::TToken token;
   pr.make(token,0x23);
   codeAdd(token,l);
   stack.push(type_array);
   if (endPos) setLastObject(type_array);
   return PRIM_PROPERTY_ARRAY;
}

int  TOtTranslator::makeproperty(TOtFuncFinder& finder,const TOtLexem& l,CSTRREF name,bool err)
{
   TOtFuncProfile& p=finder.p; TOtFuncCast& c=finder.c;
   const TRelate& rel=finder.relate;
                //   0  error
   int ret=1;   //   1  property          PRIM_PROPERTY
                //   2  property[i]       PRIM_PROPERTY_INDEX
                //   3  property[]        PRIM_PROPERTY_ARRAY
                //  -2  property.         PRIM_PROPERTY_PROPERTY

   if (match(TOtLexem::spLeftScrape)) {
      if (match(TOtLexem::spRightScrape)) return PRIM_PROPERTY_ARRAY;
      TREE_MARKER(xel) //  List
      do {
         if (! notVoidExpression() ) return 0;
         finder.param(stack[0],codes.last());
         stack.pop();
         }
      while ( match(TOtLexem::spComma) );
      if (!needBracket(TOtLexem::spRightScrape,']')) return 0;
      TREE_LEAVE(trList)
      TREE_TRANSVECTION(trItem,xel,2)
      ret=PRIM_PROPERTY_INDEX;
      }

   TOtType first;
   if (rel.mode&rltTemplate) {
      if (!err) first=p.param[p.param.low()];
      finder.removeFirst();
      }

   p.name(TOtFuncProfile::lexGet+name);

   reformParams(finder);

   c.lek=l.ofsMain();
   c.end=codes.last();
   c.mode|=c.cmProperty;
   finder.save();

   int mode=mpNotVoid; if (!err) mode|=mpNoError;
   int fget=makepoint(finder,l,mode); // ... -> ... ->
   if (!fget) {
      if (!err && (rel.mode&rltTemplate)) {
         finder.prepend(first);
         }
      return 0;
      }
   if (mode & mpPoint) return PRIM_PROPERTY_PROPERTY;

   TProperty pr;
   pr.fget=fget;
   pr.p=p; pr.c=c;
   pr.p.name(name);

   finder.reset(); finder.restore();

   p.result(id_unknown);
   finder.param(castable(pr.result()),codes.last());
   p.name(TOtFuncProfile::lexSet+name);
   pr.fset=findAndAddFuncOrFindSimple(finder);
   if (pr.fset) {
      if (p.result() != id_void) { 
         errorName(lexMess_InvalidSet.system(),l); return 0; 
         }
      pr.differ=(c.mode & c.cmThis) ^ (pr.c.mode & pr.c.cmThis) || ((pr.p.param.count()+1) != p.param.count());
      }
   property.add(pr);
   TOtType type(_id_property,1,property.last());
   stack.push(type);
   if (endPos) setLastObject(type);
   return ret;
}

int  TOtTranslator::makeuserprop(TOtProgram::TUserProperty& u,TOtFuncFinder& finder,const TOtLexem& l)
{
   TOtFuncProfile& p=finder.p; TOtFuncCast& c=finder.c;
                //   0  error
   int ret=1;   //   1  property          PRIM_PROPERTY
                //   2  property[]        PRIM_PROPERTY_INDEX
                //  -2  property.         PRIM_PROPERTY_PROPERTY

   int index=0;
   if (match(TOtLexem::spLeftScrape)) {
      TREE_MARKER(xel) //  List
      do {
         if (! notVoidExpression() ) return 0;
         finder.param(stack[0],codes.last());
         stack.pop();
         index++;
         }
      while ( match(TOtLexem::spComma) );
      if (!needBracket(TOtLexem::spRightScrape,']')) return 0;

      TREE_LEAVE(trList)
      TREE_TRANSVECTION(trItem,xel,2)
      ret=PRIM_PROPERTY_INDEX;
      }

   if (matchNo(TOtLexem::lkProperty)) {
      ret=PRIM_PROPERTY_PROPERTY;
      }

   int count=p.param.count(), must=2;
   if (u.prop.type>=TUserData::ptArrNum) must++;
   if (u.prop.type==TUserData::ptArrRec) must++;
   if (must != count) { errorName(lexMess_RangeNumberError.system(),l); return 0;}

   int iProp=1,iIndex=1;
   int iField=p.param.last()-index;

   if (u.field.index) {
      TOtProgram::TToken& token=codes[u.field.index]; token.type=token.none;
      u.field.index=0;
      p.param.remove(iField); c.tokens.remove(iField);
      }
   if (u.prop.index) {
      TOtProgram::TToken& token=codes[u.prop .index]; token.type=token.none;
      u.prop.index=0;
      p.param.remove(iProp);  c.tokens.remove(iProp);
      }

   c.add();
   if (u.prop.type>=TUserData::ptArrNum) {
      TOtType type=p.param[iIndex];
      int dept=0, cast=0, weight=0;
      if (!castable(type,TOtType::RInt)) {
         if (!castable(type,TOtType::RNum)) { errorName(lexMess_InvalidIndexProperty.system(),l);  return 0; }
         cast=cast_Num2Int;
         }
      c.TOtFuncCastable::add(cast,dept,weight);
      }
   else
      c.add();

   program->props.add(u);
   int find=program->props.last();

   reformParams(finder);
//   c.lek=pos(l);
   TProperty pr;
   pr.p=p;
   pr.c=c;
   pr.user=true;
   pr.fget=find;
   TOtAFunc *func=u.get();
   if (!func) { error(lexMess_UnknownObjectType.system(),l); return 0; }
   pr.result(func->result());
   pr.fset=find;
   property.add(pr);
   TOtType type(_id_property,1,property.last());
   stack.push(type);
   if (endPos) { setLastObject(type); setLastObject(u); }

   if (ret==PRIM_PROPERTY_PROPERTY) { if (!prefixExpressionOperator(0)) return 0; }

   return ret;
}

bool  TOtTranslator::generic(short type) const
{
   return (TOtMetaInfo::castable(type,id_TOtObjectPtr) || TOtMetaInfo::castable(type,id_TOtArrayPtr) || TOtMetaInfo::castable(type,id_TOtKeyArrPtr));
}

TOtType TOtTranslator::generic(const TOtType& type) const
{
   TOtType ret;
   if (type.isStructureOblique()) {
      int owner=abs(type.origin);
      const TLocStruct& loc=locStruct[owner];
      if (castable(type,TOtType(id_TOtRPtr,1,id_TOtArrayPtr))) {
         T_Ptr<TOtArrayPtr> arr=OT_DOWNCAST(loc.obj,TOtArrayPtr); 
         if (arr) {
            ret=arr->array.getPointerType();
            }
         }
      else if (castable(type,TOtType(id_TOtRPtr,1,id_TOtKeyArrPtr))) {
         T_Ptr<TOtKeyArrPtr> arr=OT_DOWNCAST(loc.obj,TOtKeyArrPtr); 
         if (arr) {
            ret=arr->getPointerType();
            }
         }
      else if (castable(type,TOtType(id_TOtRPtr,1,id_TOtObjectPtr))) {
         T_Ptr<TOtObjectPtr> obj=OT_DOWNCAST(loc.obj,TOtObjectPtr); 
         if (obj) {
            ret=obj->objectType();
            }
         }
      }
   return ret;
}

int  TOtTranslator::makeresult(TOtFuncFinder& finder, const TOtLexem& l, int& mode, const TOtType& type, int ret)
{
   bool yes_generic=(ret<0) && (TSimpleOperation::coll[-ret].attr() & TSimpleOperation::cArrPtrItem);
   bool result=(mode&mpResult), modif=false, value=(mode&mpNotVoid);
   TOtFuncProfile& p=finder.p;
   if (yes_generic) {
      const TOtType g=generic(type);
      if (g.id!=id_unknown) {
         p.result(g);
         modif=true;
         }
      }
   TOtType rg=p.result(), rd=rg;
   bool yes_arr=(TOtMetaInfo::castable(rg,id_TOtObjectArrNum) || TOtMetaInfo::castable(rg,id_TOtObjectArrInt) || TOtMetaInfo::castable(rg,id_TOtObjectArrStr) || TOtMetaInfo::castable(rg,id_TOtObjectArrPtr));
   if (yes_arr) mode|=mpArray;
   if (value && !castableToR(rg) && !yes_arr) {
      errorName(lexMess_InvalidResultProperty.system(),l); return 0;
      }

   if (!rd.isStructure() && rd.templateName.len()) {
      if ((rd.origin!=id_TOtDocumentNode) && (rd.origin!=id_TOtDocumentList)) {
         int idTemplate;
         if (!findTemplateWithError(rd.templateName,idTemplate,lex)) { return 0; }
         rd.id=_id_structure; rd.origin=-idTemplate;
         p.result(rd);
         modif=true;
         }
      }

   if (modif) {
      if (result) stack[0]=p.result();
      mode|=mpModif;
      }
   return ret;
}

int  TOtTranslator::makepoint(TOtFuncFinder& finder, const TOtLexem& l, int& mode)
{
   TOtFuncProfile& p=finder.p;
   TOtType type;
   if (p.param.count()) type=p.param[p.param.low()];
   int ret=findAndAddFuncOrFindSimple(finder);
   if (!ret) { if (!(mode&mpNoError)) errorFuncNotFind(finder,l); return ret; }
   return makeresult(finder,l,mode,type,ret);
}

bool TOtTranslator::index(int beg, const TOtLexem& l)   //  []
{
   TREE_MARKER(xel) //  List
   TOtFuncFinderHolder holder(adventurers); holder.tune(program,beg,main(l));
   TOtFuncProfile& p=holder.p(); TOtFuncCast& c=holder.c(); TOtFuncFinder& finder=holder.finder();
   if (stack.empty()) {
      error(lexMess_VoidObject.system());  return false;
      }
 /*
   if (castable(stack[0],TOtType(id_TOtArray))) {
      genReferencing();
      }
 */
   if (!castable(stack[0],TOtType(id_TOtRPtr)) && !castable(stack[0],TOtType::RStr)) {
      error(lexMess_NoPointer.system()); return false;
      }
   TProperty pr; pr.owner=stack[0];
   int cod=codes.last();
   holder.param(stack[0],cod);
   stack.pop();
   do {
      do {
         if (! notVoidExpression()) return false;
         holder.param(stack[0],codes.last());
         stack.pop();
         }
      while ( match(TOtLexem::spComma) );
      if (!needBracket(TOtLexem::spRightScrape,']')) return false;
      }
   while ( match(TOtLexem::spLeftScrape) );
   c.end=codes.last();
   p.name("GetItem");
   reformParams(finder);
   int delta=0;
   TOtType type=p.param[p.param.low()];
   TOtLexem lek(xel), lek_rec, le;
   if (type.isStructureOblique() && castable(type,TOtType(id_TOtRPtr,1,id_TOtObjectArrRec)) && match(TOtLexem::lkProperty)) {
      lek_rec=xel;
      if (getIdent(le) || getPath(le)) {
         int owner=abs(type.origin);
         int field=locStruct.find(owner,getText(le));
         if (field) {
            stack.push();
            int old=codes.last();
            if (!genPushFieldStruct(owner,field,le,cod+1)) return false;
            delta=codes.last()-old;
            if (delta) {
               hole(cod+delta+1,delta);
               }
            p.param(p.param.low())=type=stack[0];
            stack.pop();
            }
         else {
            errorName(lexMess_UnknownIdentify.system(),le); return false;
            }
         }
      }

   finder.save();

   int mode=mpNotVoid;
   int fget=makepoint(finder,l,mode); // [].
   if (!fget) return false;
   if (mode & mpPoint) return true; 

   pr.fget=fget;
   pr.p=p; pr.c=c;

   finder.reset(); finder.restore();

   p.result(id_unknown);
   holder.param(castable(pr.result()),codes.last());
   p.name("SetItem");
   pr.fset=findAndAddFuncOrFindSimple(finder);
   if (pr.fset && (p.result() != id_void)) {
      errorName(lexMess_InvalidSet.system(),l); return 0; 
      }
   property.add(pr);
   int prop=property.last();
   if (delta) {
      hole(prop,cod,delta);
      }
   TOtType type_prop(_id_array,1,prop);
   stack.push(type_prop);
   if (endPos) setLastObject(type_prop);
   TREE_LEAVE(trList)
   TREE_TRANSVECTION(trItem,lek,2)
   if (lek_rec.math(TOtLexem::lkProperty)) {
      if (le.math(TOtLexem::lkIdent)) {
         TREE_PUSH(trIdent,le)
         }
      else {
         TREE_PUSH(trPath,le)
         }
      TREE_TRANSVECTION(trPrecise,lek_rec,2)
      }
   return true;
}

