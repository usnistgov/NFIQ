README

example_api Output:

If example_api is able to parse both a NFIQ 2 RF Model and a valid fingerprint image, the expected output will be a list of scores generated from the respective fingerprint image. These scores are the same scores that can be obtained from the NFIQ 2 CLI CSV output. 

Each score will be printed with its respective header. Each score will be printed on a separate line.

The first score that gets printed is the NFIQ 2 Quality Score and it will appear as:
QualityScore: [score]

The next series of scores will be from actionable feedback. This includes:
EmptyImageOrContrastTooLow: [value]
to
SufficientFingerprintForeground: [value]

The next series of scores will be quality feature data. These are the scores generated by the individual metrics that comprise the NFIQ 2 quality algorithm. This includes:
FDA_Bin10_0: [value]
to
RVUP_Bin10_StdDev: [value]

The final series of scores will be speed data. These scores indicate how long (in ms) each metric took to compute. This includes: 
Frequency domain: [value]
to
Ridge valley uniformity: [value]

Comment about PGM images:
Explain the origins of these prints and include proper citation