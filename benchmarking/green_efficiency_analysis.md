# Green Tech Efficiency Analysis

## Measurement Methodology

The purpose of this experiment was to examine program execution time and understand how timing measurements can help evaluate software efficiency. The C programs used the `clock()` function from the time library to measure processor time. The elapsed time was calculated by subtracting the starting clock value from the ending clock value and dividing the result by `CLOCKS_PER_SEC`.

The baseline program performed 100,000,000 iterations of a loop. It was executed three times to observe variation between runs. Run 1 recorded 0.093846 seconds, Run 2 recorded 0.102718 seconds, and Run 3 recorded 0.094949 seconds. The average execution time was approximately **0.097171 seconds**.

The controlled instrumentation program used a dataset of 50,000 elements. It measured the total execution time and three individual stages: building the dataset, processing the dataset, and reducing the values into a checksum. Its recorded results were TOTAL: 0.000339 seconds, BUILD_DATA: 0.000144 seconds, PROCESS: 0.000124 seconds, and REDUCE: 0.000068 seconds.

## Observed Performance Differences

The baseline measurements show that execution time varied between runs. The fastest run was 0.093846 seconds, while the slowest was 0.102718 seconds. The difference was 0.008872 seconds. This demonstrates that repeated executions can produce slightly different timing results, even when the program performs the same number of iterations.

In the instrumentation experiment, dataset creation took 0.000144 seconds, processing took 0.000124 seconds, and checksum reduction took 0.000068 seconds. Dataset creation was the longest measured stage, followed by processing and reduction. The total measured time was 0.000339 seconds.

The three stage measurements add up to 0.000336 seconds. This is slightly lower than the recorded total, which is expected because the total measurement also covers the small intervals between the individual stage measurements.

These results describe two different workloads. Therefore, the lower total time of the instrumentation program should not be interpreted as proof that it is more efficient than the baseline program.

## Relation Between Runtime and Energy Consumption

Execution time can help engineers reason about potential energy consumption because a program that keeps a processor busy for longer may use more energy. However, runtime alone does not measure electricity usage.

In this experiment, the baseline program averaged 0.097171 seconds, while the instrumentation program recorded 0.000339 seconds for its different workload. These figures show the measured execution times, but they do not establish which program consumed less energy. Actual energy consumption would require additional measurements, such as processor power or energy readings.

## Limitations of the Experiment

One limitation is that the two programs perform different amounts and types of work. The baseline program executes 100 million loop iterations, whereas the instrumentation program operates on 50,000 dataset elements. Their execution times are therefore not a controlled comparison of equivalent tasks.

Another limitation is that the instrumentation experiment was recorded only once. More repeated runs would provide a better understanding of timing variation. The experiment also did not directly measure CPU power, electricity consumption, or environmental impact. The results may additionally be affected by the computer's hardware, operating system activity, and background processes.

## Practical Engineering Takeaway

This experiment demonstrates the value of measuring execution time rather than relying on assumptions about software performance. Separating a program into stages helps identify which operations take the most time. In the instrumentation results, dataset creation was the longest stage at 0.000144 seconds.

Engineers can use this information to identify areas worth investigating before attempting optimisation. However, they should repeat measurements, compare equivalent workloads, and use suitable energy-monitoring tools when evaluating sustainability. Efficient software engineering requires evidence, careful measurement, and an understanding of the limitations of the data.
