# microview

sensor values get reported via xbee, rate limited by minimum delta (“sensitivity”), and min time between reporting (“rate”).  the host can adjust the sensitivity by sending “s:5” (don’t report changes smaller than 5), and can adjust the rate by sending “r:1000” (report max ever 1 second)


![Circuit](https://cloud.githubusercontent.com/assets/4671202/7906342/37c5eaaa-07de-11e5-82c9-4527616016b4.JPG)
