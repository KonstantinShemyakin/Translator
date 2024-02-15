    enum T_SQLWordType { 
                   sqNone           , sqAbort          , sqAccept         , sqAccess         , sqAdd            ,
                   sqAll            , sqAlter          , sqAnd            , sqAny            , sqAs             ,
                   sqAsc            , sqAudit          , sqAssert         , sqAssign         , sqAt             ,
                   sqAuthorization  , sqAvg            , sqBegin          , sqBetween        , sqBody           ,
                   sqBoolean        , sqBy             , sqCase           , sqChar           , sqCharBase       ,
                   sqCheck          , sqClose          , sqCluster        , sqClusters       , sqColauth        ,
                   sqColumn         , sqColumns        , sqComment        , sqCommit         , sqCompress       ,
                   sqConnect        , sqConstant       , sqCount          , sqCrash          , sqCross          ,
                   sqCreate         , sqCurrent        , sqCursor         , sqCurrval        , sqDatabase       , 
                   sqData_base      , sqDate           , sqDba            , sqDebugoff       , sqDebugon        , 
                   sqDecimal        , sqDeclare        , sqDefault        , sqDefinition     , sqDelay          , 
                   sqDelete         , sqDelta          , sqDesc           , sqDigits         , sqDispose        , 
                   sqDistinct       , sqDo             , sqDrop           , sqElse           , sqElsif          , 
                   sqEnd            , sqEntry          , sqEscape         , sqException      , sqExceptionInit  , 
                   sqExclusive      , sqExists         , sqExit           , sqFalse          , sqFetch          , 
                   sqFile           , sqFloat          , sqFor            , sqForm           , sqFrom           , 
                   sqFull           , sqFunction       , sqGeneric        , sqGoto           , sqGrant          , 
                   sqGroup          , sqHaving         , sqIdentfied      , sqIf             , sqImmediate      , 
                   sqIn             , sqIncrement      , sqIndex          , sqIndexes        , sqInitial        , 
                   sqIndicator      , sqInner          , sqInsert         , sqInteger        , sqIntersect      , 
                   sqInto           , sqIs             , sqJoin           , sqLeft           , sqLevel          ,
                   sqLike           , sqLimit          , sqLimited        , sqLock           , sqLong           ,
                   sqLoop           , sqMax            , sqMaxextents     , sqMin            , sqMinus          ,
                   sqMod            , sqMode           , sqModify         , sqNatural        , sqNextval        , 
                   sqNew            , sqNoaudit        , sqNocompress     , sqNot            , sqNowait         , 
                   sqNull           , sqNumber         , sqNumberBase     , sqOf             , sqOffline        , 
                   sqOffset         , sqOn             , sqOnline         , sqOpen           , sqOption         , 
                   sqOr             , sqOrder          , sqOthers         , sqOut            , sqOuter          , 
                   sqPackage        , sqPartition      , sqPctfree        , sqPragma         , sqPrior          , 
                   sqPrivate        , sqPrivileges     , sqProcedure      , sqPublic         , sqRaise          , 
                   sqRange          , sqRaw            , sqRecord         , sqRelease        , sqRem            , 
                   sqRename         , sqReplace        , sqResource       , sqReturn         , sqReturning      , 
                   sqReverse        , sqRevoke         , sqRight          , sqRollback       , sqRow            , 
                   sqRowid          , sqRowlabel       , sqRownum         , sqRows           , sqRowtype        , 
                   sqRun            , sqSavepoint      , sqSchema         , sqSelect         , sqSeparate       , 
                   sqSession        , sqSet            , sqShare          , sqSize           , sqSmallint       , 
                   sqSome           , sqSpace          , sqSql            , sqSqlcode        , sqSqlerrm        , 
                   sqStart          , sqStatement      , sqStddev         , sqSubtype        , sqSuccessful     , 
                   sqSum            , sqSynonym        , sqSysdate        , sqTabauth        , sqTable          , 
                   sqTables         , sqTask           , sqTerminate      , sqThen           , sqTo             , 
                   sqTrigger        , sqTrue           , sqType           , sqUid            , sqUnion          , 
                   sqUnionall       , sqUnique         , sqUpdate         , sqUse            , sqUser           , 
                   sqUsing          , sqValidate       , sqValues         , sqVarchar        , sqVarchar2       , 
                   sqVariance       , sqView           , sqViews          , sqWhen           , sqWhenever       , 
                   sqWhere          , sqWhile          , sqWith           , sqWork           , sqXor            , 
                   sqDeterministic  , sqResultCache    , sqConstraint,
                   sqONLY           ,
                   sqVERSIONS       ,
                   sqSCN            ,
                   sqTIMESTAMP      ,
                   sqMINVALUE       ,
                   sqMAXVALUE       ,
                   sqSUBPARTITION   ,
                   sqSAMPLE         ,
                   sqBLOCK          ,
                   sqSEED           ,
                   sqREAD           ,
                   sqNOCYCLE        ,
                   sqROLLUP         ,
                   sqCUBE           ,
                   sqGROUPING       ,
                   sqSETS           ,
                   sqMODEL          ,
                   sqNAV            ,
                   sqIGNORE         ,
                   sqKEEP           ,
                   sqDIMENSION      ,
                   sqSINGLE         ,
                   sqREFERENCE      ,
                   sqUPDATED        ,
                   sqMAIN           ,
                   sqMEASURES       ,
                   sqRULES          ,
                   sqUPSERT         ,
                   sqAUTOMATIC      ,
                   sqSEQUENTIAL     ,
                   sqITERATE        ,
                   sqUNTIL          ,
                   sqDECREMENT      ,
                   sqSIBLINGS       ,
                   sqNULLS          ,
                   sqFIRST          ,
                   sqLAST           ,
                   sqWAIT           ,
                   sqLOG            ,
                   sqERRORS         ,
                   sqREJECT         ,
                   sqUNLIMITED      ,
                   sqVALUE          ,  


                   sqNAN,
                   sqINFINITE,
                   sqA,
                   sqEMPTY,
                   sqMEMBER,
                   sqSUBMULTISET,
                   sqUNDER_PATH,
                   sqEQUALS_PATH,
                   sqREGEXP_LIKE,
                   sqLIKEC,
                   sqLIKE2,
                   sqLIKE4,
                   sqPRESENT

};
