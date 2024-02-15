//%%
S_          : bnf                        
            ;
bnf         : bnf rules
            |
            ;
rules       : rule
            | rules  '|' symbol_list
            ;
rule        : <Space> <Separator,BNFSet> symbol_list
            ;
symbol_list : symbol_list <Space>
            |
            ;


