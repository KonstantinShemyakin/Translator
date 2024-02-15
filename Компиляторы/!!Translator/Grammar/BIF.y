//%%
S_          : rules                        
            ;
rules       : rules rule
            | rule
            ;
rule        : <Space> <Separator,BNFSet> item_list <Meta,Semicolon>
            ;
item_list   : item_list item
            | item_list <Space>
            | item
            | <Space>
            ;
item        : <Meta,LeftScrape> or_list <Meta,RightScrape>
            | <Meta,LeftScrape> or_list <Meta,RightScrape> <Meta,Ellipsis>
            | <Meta,LeftCramp>  or_list <Meta,RightCramp>
            ;
or_list     : or_list <Meta,Or> item_list
            | item_list
            ;


