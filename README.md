magwater
========

Spark Core Magnetic Watermeter Monitor

========

The goal of this project is to monitor my water usage as stupidly accurately as I can.  Today I already have an IR based system but I've found the acuracy too low (sink usage doesn't always register for example).  I found a few references to doing this with hall effect sensors:

http://forum.arduino.cc/index.php?topic=63452.0
http://www.edcheung.com/automa/water.htm

I have a neptune water meter and the field is indeed rather weak.  I decided to look for something that could detect these signals but was simpler and cheaper.  Given that it is something like 1/5 of the earths magnetic field I guessed a digital compass module should be able to read it.  Reading through some spec sheets confirmed my suspicion.

I purchased a broken out mag3110 from Sparkfun https://www.sparkfun.com/products/10619

$15 seems a lot cheaper than the ultra sensitve magnetic field detector used above.  Plus I can use it for other projects if it doesn't work.

My main fear is that the max sample rate (80hz) will be to slow.  I don't know how fast the field will spin and my simple signal processing probably needs at least 4 samples per revolution or something.

Given the 3v part I decided to use my Spark Core for this project http://spark.io  Right now the i2c seems to sometimes get short reads (not sure why yet, but I submitted a patch to timeout reads so it won't just hang)

=========

I've since found this.  I find it funny that the author didn't note that you can just buy the same thing that is in your cell phone when they demoed that a cell phone is sensitve enough.  I rather like that all of the a/d and amplification is done for me.

http://www.instructables.com/id/Monitoring-residential-water-usage-by-reading-muni/

========

Somehow I missed the Honeywell compass which seems just better overall.  It would seem I can get 160hz out of it (funny it can only do this in per-sample mode, not continuous...  oh well).  It also has a slight better sensitivty and noise.  I haven't yet tried it out.

https://www.sparkfun.com/products/10530

=======

Feel free to give me feedback, I hope to get this hooked up to my meter soon.