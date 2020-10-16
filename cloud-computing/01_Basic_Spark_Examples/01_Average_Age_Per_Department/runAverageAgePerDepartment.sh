# Use the spark-submit operattion to execute the python file
# The tee function copies the output of the executed application to
# a file called output, which is then displayed and immediately deleted.
spark-submit AverageAgePerDepartment.py|tee temp-output

echo " "
echo " "
echo " "
echo " "
echo " "
echo " "
echo "------ SPARK SUBMIT OUTPUT ------"
cat temp-output

rm temp-output
