

# Procedures #

The tests procedures are described in JPEG 2000 part 4 (15444-4), available [here](http://www.openjpeg.org/conformance/T.803e.pdf).

# Files #

All files required for testing the conformance of openjpeg are available [here](https://drive.google.com/file/d/0B9lJIDXo2oPYZlNnVnRKRFdwVDg/edit?usp=sharing)

# Decoder validation #

The decoder should be tested in the following way:
  1. Decode the test codestream
  1. Compute the MSE and the peak error, compared to the corresponding reference image.
  1. Compare the MSE and the peak error to the tolerated values.

## Decoder tests suite ##

Here is the list of tests achieved to validate the openjpeg decoder.

```
j2k_to_image -i p0_01.j2k -o p0_01.pgx
j2k_to_image -i p0_02.j2k -o p0_02.pgx
j2k_to_image -i p0_03.j2k -o p0_03.pgx
j2k_to_image -i p0_04.j2k -o p0_04.pgx
j2k_to_image -i p0_05.j2k -o p0_05.pgx
j2k_to_image -i p0_06.j2k -o p0_06.pgx
j2k_to_image -i p0_07.j2k -o p0_07.pgx
j2k_to_image -i p0_08.j2k -o p0_08.pgx
j2k_to_image -i p0_09.j2k -o p0_09.pgx
j2k_to_image -i p0_10.j2k -o p0_10.pgx
j2k_to_image -i p0_11.j2k -o p0_11.pgx
j2k_to_image -i p0_12.j2k -o p0_12.pgx
j2k_to_image -i p0_13.j2k -o p0_13.pgx
j2k_to_image -i p0_14.j2k -o p0_14.pgx
j2k_to_image -i p0_15.j2k -o p0_15.pgx
j2k_to_image -i p0_16.j2k -o p0_16.pgx
j2k_to_image -i p1_01.j2k -o p1_01.pgx
j2k_to_image -i p1_02.j2k -o p1_02.pgx
j2k_to_image -i p1_03.j2k -o p1_03.pgx
j2k_to_image -i p1_04.j2k -o p1_04.pgx
j2k_to_image -i p1_05.j2k -o p1_05.pgx
j2k_to_image -i p1_06.j2k -o p1_06.pgx
j2k_to_image -i p1_07.j2k -o p1_07.pgx
```

# Encoder validation #

The encoder should be tested in the following way:
  1. Encode a test image with a given set of parameters
  1. Try to decode it with Kakadu.
  1. Compare the original image to the decoded one and verify that the MSE is below the tolerated MSE defined for this test (typically, MSE = 0 for lossless tests, etc).

## Encoder tests suite ##

Here is the list of tests to achieve to validate the openjpeg encoder

TBD

.