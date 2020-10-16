'''
This is a very basic pyspark map-reduce example for calculating average 
age per department given Department and age per person.

Uses the following:
1) Spark session
2) Basic Dataframe created in the program itself
3) Conversion of Dataframe to RDD
4) Basic mapper and basic reducer using lambda functions
5) Collector
6) Spark data API to compare results

Use the runAverageAgePerDepartment.sh script in the same directory to 
execute this using spark-submit.

Alternatively, just try python3 AverageAgePerDepartment.py
'''


#The most important step  - import pyspark :)
import pyspark

#Set up the spark session. This will act as a unified entry point
# for the spark application.
# From Spark 2.0, you just need to set a Spark session
# which provides a spark context, hive context and SQL context.
spark = pyspark.sql.SparkSession.builder.getOrCreate()

# In Spark, DataFrames are the distributed collections of data, 
# organized into rows and columns. Each column in a DataFrame has 
# a name and an associated type. DataFrames are similar to 
# traditional database tables, which are structured and concise.
departmentData = spark.createDataFrame(    
    [
        ('ECE', 23),
        ('ECE', 25),
        ('CS', 22),
        ('CS', 24)
    ],
    ['dept', 'age']
)

# Display the input data
print("Input Data")
departmentData.show()

# Display the result using map and reduce
print("Result using map reduce")

'''
# Steps followed using map reduce to calculate average age per department
1. Convert the dataframe to rdd (Resilient Distributed Database). This is needed to be able to 
    run map and reduce.
2. Run the first mapper - this creates a map in with entries in the following manner 
    (for the example dataframe above):
    [('ECE', [23, 1]), ('ECE', [25, 1]), ('CS', [22, 1]), ('CS', [24, 1])]
    On a multinode cluster, these entries will be likely computed in separate nodes.

3. Run the first reducer - this will take the key from the map in step 2 (dept in this case) 
    and sum all the first element for each key and the second element for each key separately. 
    The result will be the sum of all ages and the count of students for each department:
    [('CS', [46, 2]), ('ECE', [48, 2])]
    (Note that the keys have already been sorted at this step)

4. Run the second mapper - this will divide the first element (sum of ages) by the second
    element (number of persons) to calculate the average age for each department.
    The final result will be
    [['CS', 23.0], ['ECE', 24.0]]

5. Finally collect the data into a single unit that can be accessed.
'''

print(departmentData .rdd.map(lambda person: (person.dept,[person.age,1])) \
    .reduceByKey(lambda person1, person2: [person1[0] + person2[0], person1[1] + person2[1] ]) \
    .map(lambda dept: [dept[0],dept[1][0]/dept[1][1] ]) \
    .collect())

print(" ")
print(" ")

# This effectively does the same as above under the hood, but uses
# a more SQL like querying to simplify data operations.
print("Result using Spark Data API")
departmentData.groupBy("dept").avg("age").show()