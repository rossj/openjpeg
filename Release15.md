# Introduction #

Let's list the things remainings to do before v1.5.

v1.5 is frozen, this means no NEW feature should go in, only bug fixes.

# Summary of tests failing #

For the moment we have worked on the decoding part and the encoding part must be considered as unstable so all test with prefix ENC should ignored for the moment in the trunk. broken, broken2, broken3 and broken4 should failed.

If you used dashboard filter, you can see that it remains 38 tests linked to the fact when we decode some C0 (Cclass0) conformance files we produce multiband files but we must not because reference pgx file have only one. 36 tests are linked to this point. I am not sure to understand what we can do to avoid this point, perhaps Antonin have more ideas on it.
For the trunk, we have a strong problem with p0\_07.j2k file described in [issue 80](https://code.google.com/p/openjpeg/issues/detail?id=80) http://code.google.com/p/openjpeg/issues/detail?id=80 which is not correctly decoded.

For the branch 1.5 which will be the next release, the list of tests with problems not linked to C0P0 or C0P1 files are listed here http://my.cdash.org/viewTest.php?onlyfailed&buildid=264729&filtercount=3&showfilters=1&filtercombine=and&field1=testname/string&compare1=64&value1=C0P0&field2=testname/string&compare2=64&value2=C0P1&field3=testname/string&compare3=64&value3=broken <http://my.cdash.org/viewTest.php?onlyfailed&buildid=264729&filtercount=3&showfilters=1&filtercombine=and&field1=testname/string&compare1=64&value1=C0P0&field2=testname/string&compare2=64&value2=C0P1&field3=testname/string&compare3=64&value3=broken>

# Script #

See [script](http://code.google.com/p/openjpeg/source/browse/dev-utils/scripts/script.sh) to generate the page:

# Details #

Quite a few tests are still failings:

**http://my.cdash.org/viewTest.php?onlyfailed&buildid=269771**

|ETS-C0P1-p1\_04.j2k-[r0](https://code.google.com/p/openjpeg/source/detail?r=0)-compare2ref|Failed|Passed|0.08|Completed (Failed)|
|:-----------------------------------------------------------------------------------------|:-----|:-----|:---|:-----------------|
|ETS-C0P1-p1\_04.j2k-[r3](https://code.google.com/p/openjpeg/source/detail?r=3)-compare2ref|Failed|Passed|0.00|Completed (Failed)|
|ETS-C1P0-p0\_07.j2k-compare2ref                                                           |Failed|Passed|0.92|Completed (Failed)|
|ETS-C1P0-p0\_07.j2k-decode                                                                |Failed|Passed|0.10|Completed (Failed)|
|NR-C0P1-p1\_04.j2k-[r0](https://code.google.com/p/openjpeg/source/detail?r=0)-compare2base|Failed|Passed|0.00|Completed (Failed)|
|NR-C0P1-p1\_04.j2k-[r3](https://code.google.com/p/openjpeg/source/detail?r=3)-compare2base|Failed|Passed|0.00|Completed (Failed)|
|NR-C1P0-p0\_07.j2k-compare2base                                                           |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-123.j2c-3-compare\_dump2base                                                       |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken.jp2-4-compare\_dump2base                                                    |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken.jp2-4-decode                                                                |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken.jp2-4-dump                                                                  |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken2.jp2-5-compare\_dump2base                                                   |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken2.jp2-5-decode                                                               |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken2.jp2-5-dump                                                                 |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken3.jp2-6-compare\_dump2base                                                   |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken3.jp2-6-decode                                                               |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken3.jp2-6-dump                                                                 |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken4.jp2-7-compare\_dump2base                                                   |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken4.jp2-7-decode                                                               |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken4.jp2-7-dump                                                                 |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-bug.j2c-8-compare\_dump2base                                                       |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-text\_GBR.jp2-29-compare\_dump2base                                                |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-text\_GBR.jp2-29-decode                                                            |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-text\_GBR.jp2-29-dump                                                              |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-Bretagne2.ppm-4-compare\_dec-ref-out2base                                          |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-Bretagne2.ppm-4-compare\_dump2base                                                 |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-Bretagne2.ppm-4-decode-ref                                                         |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-Bretagne2.ppm-4-dump                                                               |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-Bretagne2.ppm-4-encode                                                             |Failed|Passed|2.85|Completed (SEGFAULT)|
|NR-ENC-Bretagne2.ppm-6-compare\_dump2base                                                 |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_4\_2K\_24\_185\_CBR\_WB\_000.tif-12-compare\_dec-ref-out2base                   |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_4\_2K\_24\_185\_CBR\_WB\_000.tif-12-compare\_dump2base                          |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_5\_2K\_24\_235\_CBR\_STEM24\_000.tif-13-compare\_dec-ref-out2base               |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_5\_2K\_24\_235\_CBR\_STEM24\_000.tif-13-compare\_dump2base                      |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_6\_2K\_24\_FULL\_CBR\_CIRCLE\_000.tif-14-compare\_dec-ref-out2base              |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_6\_2K\_24\_FULL\_CBR\_CIRCLE\_000.tif-14-compare\_dump2base                     |Failed|Passed|0.00|Completed (Failed)|
|NR-file9.jp2-compare\_dump2base                                                           |Failed|Passed|0.00|Completed (Failed)|
|NR-p0\_07.j2k-compare\_dump2base                                                          |Failed|Passed|0.00|Completed (Failed)|
|NR-p0\_07.j2k-dump                                                                        |Failed|Passed|0.10|Completed (Failed)|

while with -m32 flag:

|ETS-C0P1-p1\_04.j2k-[r0](https://code.google.com/p/openjpeg/source/detail?r=0)-compare2ref|Failed|Passed|0.16|Completed (Failed)|
|:-----------------------------------------------------------------------------------------|:-----|:-----|:---|:-----------------|
|ETS-C0P1-p1\_04.j2k-[r3](https://code.google.com/p/openjpeg/source/detail?r=3)-compare2ref|Failed|Passed|0.01|Completed (Failed)|
|ETS-C1P0-p0\_07.j2k-compare2ref                                                           |Failed|Passed|1.84|Completed (Failed)|
|ETS-C1P0-p0\_07.j2k-decode                                                                |Failed|Passed|0.15|Completed (Failed)|
|NR-C0P1-p1\_04.j2k-[r0](https://code.google.com/p/openjpeg/source/detail?r=0)-compare2base|Failed|Passed|0.00|Completed (Failed)|
|NR-C0P1-p1\_04.j2k-[r3](https://code.google.com/p/openjpeg/source/detail?r=3)-compare2base|Failed|Passed|0.00|Completed (Failed)|
|NR-C1P0-p0\_04.j2k-compare2base                                                           |Failed|Passed|2.04|Completed (Failed)|
|NR-C1P0-p0\_05.j2k-compare2base                                                           |Failed|Passed|4.01|Completed (Failed)|
|NR-C1P0-p0\_06.j2k-compare2base                                                           |Failed|Passed|0.29|Completed (Failed)|
|NR-C1P0-p0\_07.j2k-compare2base                                                           |Failed|Passed|0.00|Completed (Failed)|
|NR-C1P1-p1\_02.j2k-compare2base                                                           |Failed|Passed|2.04|Completed (Failed)|
|NR-C1P1-p1\_03.j2k-compare2base                                                           |Failed|Passed|3.97|Completed (Failed)|
|NR-C1P1-p1\_04.j2k-compare2base                                                           |Failed|Passed|5.14|Completed (Failed)|
|NR-C1P1-p1\_05.j2k-compare2base                                                           |Failed|Passed|1.62|Completed (Failed)|
|NR-DEC-123.j2c-3-compare\_dump2base                                                       |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken.jp2-4-compare\_dump2base                                                    |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken.jp2-4-decode                                                                |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken.jp2-4-dump                                                                  |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken2.jp2-5-compare\_dump2base                                                   |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken2.jp2-5-decode                                                               |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken2.jp2-5-dump                                                                 |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken3.jp2-6-compare\_dump2base                                                   |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken3.jp2-6-decode                                                               |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken3.jp2-6-dump                                                                 |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken4.jp2-7-compare\_dump2base                                                   |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken4.jp2-7-decode                                                               |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-broken4.jp2-7-dump                                                                 |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-bug.j2c-8-compare\_dump2base                                                       |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-text\_GBR.jp2-29-compare\_dump2base                                                |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-text\_GBR.jp2-29-decode                                                            |Failed|Passed|0.00|Completed (Failed)|
|NR-DEC-text\_GBR.jp2-29-dump                                                              |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-Bretagne2.ppm-4-compare\_dec-ref-out2base                                          |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-Bretagne2.ppm-6-compare\_dump2base                                                 |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_4\_2K\_24\_185\_CBR\_WB\_000.tif-12-compare\_dec-ref-out2base                   |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_4\_2K\_24\_185\_CBR\_WB\_000.tif-12-compare\_dump2base                          |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_5\_2K\_24\_235\_CBR\_STEM24\_000.tif-13-compare\_dec-ref-out2base               |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_5\_2K\_24\_235\_CBR\_STEM24\_000.tif-13-compare\_dump2base                      |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_6\_2K\_24\_FULL\_CBR\_CIRCLE\_000.tif-14-compare\_dec-ref-out2base              |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-X\_6\_2K\_24\_FULL\_CBR\_CIRCLE\_000.tif-14-compare\_dump2base                     |Failed|Passed|0.00|Completed (Failed)|
|NR-file9.jp2-compare\_dump2base                                                           |Failed|Passed|0.00|Completed (Failed)|
|NR-p0\_07.j2k-compare\_dump2base                                                          |Failed|Passed|0.00|Completed (Failed)|
|NR-p0\_07.j2k-dump                                                                        |Failed|Passed|0.15|Completed (Failed)|

# Summary #

This means on 64bits the following tests are failing:

|NR-ENC-Bretagne2.ppm-4-compare\_dump2base|Failed|Passed|0.00|Completed (Failed)|
|:----------------------------------------|:-----|:-----|:---|:-----------------|
|NR-ENC-Bretagne2.ppm-4-decode-ref        |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-Bretagne2.ppm-4-dump              |Failed|Passed|0.00|Completed (Failed)|
|NR-ENC-Bretagne2.ppm-4-encode            |Failed|Passed|2.85|Completed (SEGFAULT)|

while on 32bits:


|NR-C1P0-p0\_04.j2k-compare2base|Failed|Passed|2.04|Completed (Failed)|
|:------------------------------|:-----|:-----|:---|:-----------------|
|NR-C1P0-p0\_05.j2k-compare2base|Failed|Passed|4.01|Completed (Failed)|
|NR-C1P0-p0\_06.j2k-compare2base|Failed|Passed|0.29|Completed (Failed)|
|NR-C1P1-p1\_02.j2k-compare2base|Failed|Passed|2.04|Completed (Failed)|
|NR-C1P1-p1\_03.j2k-compare2base|Failed|Passed|3.97|Completed (Failed)|
|NR-C1P1-p1\_04.j2k-compare2base|Failed|Passed|5.14|Completed (Failed)|
|NR-C1P1-p1\_05.j2k-compare2base|Failed|Passed|1.62|Completed (Failed)|