import pyspark

sc = pyspark.SparkContext("local", "Average age of Employee per Department")

spark = pyspark.sql.SparkSession.builder.getOrCreate()

data = spark.createDataFrame(    
    [
        ('ECE', 23),
        ('ECE', 25),
        ('CS', 22),
        ('CS', 24)
    ],
    ['dept', 'age']
)

print("Input Data")
data.show()

print("Result using map reduce")
print(data.rdd.map(lambda person: (person.dept,[person.age,1])) \
        .reduceByKey(lambda person1, person2: [person1[0] + person2[0], person1[1] + person2[1] ])
        .map(lambda dept: [dept[0],dept[1][0]/dept[1][1] ])
        .collect())
print(" ")
print(" ")

print("Result using map reduce")
data.groupBy("dept").avg("age").show()