# microview

sensor values get reported via xbee.  
  
Reporting can be rate limited by:  
-Minimum delta (“sensitivity”) (don't report changes smaller than N)  
-Minimum time between reporting ("rate").  

The bridge can adjust the sensitivity by sending:
"s:5” (don’t report changes smaller than 5)  
or  
"r:1000" (set rate to 1000 ms)  

  

![Circuit](https://cloud.githubusercontent.com/assets/4671202/7906342/37c5eaaa-07de-11e5-82c9-4527616016b4.JPG)
