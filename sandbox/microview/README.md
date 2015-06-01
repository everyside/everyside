# microview

sensor values get reported via xbee, rate limited by minimum delta (“sensitivity”), and min time between reporting (“rate”).  the host can adjust the sensitivity by sending “s:5” (don’t report changes smaller than 5), and can adjust the rate by sending “r:1000” (report max ever 1 second)
