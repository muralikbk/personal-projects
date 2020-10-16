# Cloud computing instructions for OSX - Homebrew, Python, pySpark/Scala and Hadoop

## Introduction
These are the steps required to get started with cloud computing using Spark, Python3 (Pyspark) and Hadoop. These instructions are for MacOS (OSX) - specifically Catalina 10.15.6. While there is little reason to think that the instructions will change significantly for future versions, do keep an eye out and of course, update this document if things do change.

Note that whenever a command is indicated, it is expected that you execute it on the terminal.

This guide should ideally work for Linux too; do document any deviations from the instructions if needed.

*Note that the **~\.zshrc** file is being edited here as Osx uses the zsh shell by default (as of OSX 10.15.6). If the shell changes or if you are using Linux, see find out what the **rc** config file for your shell. For example, for bash shell, this will be **~\.bash_profile**. This will be located in your home directory (indicated by the **~**).*

## Pre-Requisites
### Install Homebrew
Think of homebrew as an app store for programmers on Mac. Unless you are purely programming for OSx or iOS, you will most likely need this at some point of time. Install homebrew using the following command on your terminal:
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
```
Homebrew is also useful to update all packages installed through it instead of having to update them manually one by one.
You can update all installed Homebrew packages using the command:
```
brew update && brew upgrade
```

### Install XCode command line tools
You can simply install XCode from the App store. Since 2014, the command line tools have been a part of the XCode framework, so no need to install them separately.
If you are having trouble installing XCode (or don’t want to), you can install just the command line tools for XCode from the site https://developer.apple.com/download/more/. 

### Install Java 8/11
Depending on which version of hadoop/Java you are looking to install, install OpenJDK (See https://cwiki.apache.org/confluence/display/HADOOP/Hadoop+Java+Versions) to see which are the latest versions fully supported.
OpenJDK is preferred because Oracle JDK requires an enterprise licence - if you have access to that, you can use the latest supported version of Oracle JDK. As of today JDK 8 and 11 are supported. We are installing the adoptopenjdk(https://adoptopenjdk.net/) which installs the pre-built versions of JDK to reduce complexity.

PFB instructions for installing the OpenJDK 11:
```
brew update
brew tap adoptopenjdk/openjdk
brew cask install adoptopenjdk11
```

Confirm the install using the below command:
```
/usr/libexec/java_home
```

If there is no other version of Java installed, the output of this should be:
```
/Library/Java/JavaVirtualMachines/adoptopenjdk-8.jdk/Contents/Home
```

This essentially means that the “java home”, which is used to determine the default Java version will point towards the OpenJDK version you just installed. You can confirm this by running the command:
```
java -version
```

The output would ideally be (for OpenJDK 11.0.x):
```
openjdk version "11.0.8" 2020-07-14
OpenJDK Runtime Environment AdoptOpenJDK (build 11.0.8+10)
OpenJDK 64-Bit Server VM AdoptOpenJDK (build 11.0.8+10, mixed mode)
```

You can optionally set this executable as your main JAVA version using the following command. This is useful if you want the 11.0.x version of Java to be your default system wide. However, we will configure this within the other applications here, so this isn’t necessary.
```
export JAVA_HOME=`/usr/libexec/java_home -v 11.0`
```


## Install Spark, pySpark and Scala
### Installing Spark
Apache Spark (https://spark.apache.org/) is a cluster computing framework designed for fast Hadoop computation. This is the framework that pySpark or Scala communicates with when you run the appropriate code. You can install spark using the command:
```
brew install apache-spark
```

After installing, you can verify the spark installation by running the command:
```
spark-shell
```

This should start the spark shell and you will be able to give direct commands to spark. Note that this says scala because the default language used to interact with Spark is scala; this doesn’t mean that scala is fully installed or other languages can’t be used.

To quit the spark shell use the following command within the shell:
**scala>**`:quit`

###
Spark is quite powerful - however, programming directly with spark is definitely a pain - the equivalent of programming using direct processor instructions. As a result, it can become really cumbersome to run complex data analytics on it. Fortunately, we have spark libraries for both Python (pySpark) and Java (Scala) that abstract away a lot of inner workings of spark so you can focus on data analytics or have an easier time dipping your toes into the ocean of big data processing!

#### Installing pySpark
To install Python and pySpark, use the following commands:
```
brew install python3
pip3 install pyspark
```

Next, set up the spark environment by adding the following to the **~\.zshrc** file:
```
export SPARK_HOME=/usr/local/lib/python3.7/site-packages/pyspark
export PYSPARK_PYTHON=python3
```




Now, add the following contents to a test python file, say pysparktest.py.
```
from pyspark import SparkContext sc = SparkContext(master = 'local[*]') 

print(sc.version)
print(sc.pythonVer)
print(sc.master)
print(str(sc.sparkHome))
print(sc.appName)
print(sc.applicationId)
print(sc.defaultParallelism)
print(sc.defaultMinPartitions) 
sc.stop()
```

Execute this test file using the command:
```
python3 pysparktest.py
```

You should get the following output:
```
3.0.1
3.8
local[*]
None
pyspark-shell
local-1601065269562
4
2
```

#### Installing Scala
You can install Scala using the following command:
```
brew install scala
```


## Installing Hadoop
### Enabling SSH on your machine
First you need to enable ssh on your machine. For this, go to System Preferences -> Sharing. Enable the “Remote Login” and in the dialog box that appears, select the option that indicates “Allow remote login for local network”. (This is to ensure that someone cannot remote into your machine from the internet. If you know what you are doing and desire this, you can select the “Allow all connections” option). 
This starts the ssh server, which is necessary for hadoop server access. You can test this using the command:
```
ssh localhost
```

The command prompt would ask if you are okay with adding this computer to your list of computers (this is a one time question). You can enter your password and you will again be faced with the command prompt. Type the following command to exit:
```
exit
```
You should see the output “Connection to localhost closed.”

### Enable passwordless ssh on your machine
This step is necessary for hadoop - hadoop tries to start multiple server instances for various tasks on your localhost - it expects that it will be able to ssh into the local machine without any manual intervention required. In security conscious applications, this is done through kerberos based authentication tickets; here however, we will just set up an RSA key to enable passwordless ssh on the machine.

Check the status of your current RSA keys using the following command:
```
ls ~/.ssh
```

You should see the files id_rsa, id_rsa.pub (and maybe some others). If you don’t, you need to run the following command to generate an RSA key
```
ssh-keygen -t rsa
```

Once you have the RSA key files, run the following command:
```
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
```

This adds the RSA key to your list of authorized keys; as in if you have this key on a machine, you can do a passwordless login to your machine. In this case, it is from your machine to your machine, so another user won’t be able to do a passwordless login to your machine without this key file (so don’t give it away please).

Now, you can ssh into localhost without using your password each time you try. You can test this using the command:
```
ssh localhost
```

The command line will directly show the last login time and will not expect a password. 
Type the following command to exit:
```
exit
```
You should see the output “Connection to localhost closed.”

### Install Hadoop using homebrew
Now you can install Hadoop just using the command:
```
brew install hadoop
```

This will install Hadoop in your machine. Once installation is complete, you will likely see a location after “Installing Hadoop” - this will likely be /usr/local/Cellar/hadoop/<version>. An additional symbolic link at /usr/local/opt/hadoop will also be created to the above directory. 
We will refer to the symbolic link as **hadoop_dir** for the next few steps.

### Configure Hadoop server
Now you need to edit several config files to configure hadoop to run on your local host.
First, navigate to the folder: /**hadoop_dir**/libexec/etc/hadoop. All the files below are in this folder.

#### hadoop-env.sh
Open the file hadoop-env.sh. In this, file, uncomment the entry(remove the # in front of the line):
`export HADOOP_OPTS="$HADOOP_OPTS -Djava.net.preferIPv4Stack=true -Djava.security.krb5.realm= -Djava.security.krb5.kdc="`

This will ensure that the hadoop server will be able to start up passwordless
*Note: JAVA_HOME in this file need not be edited for OSX. It may need to be set here or in the universal environment variable for Linux though 
core-site.xml*
Open the file core-site.xml. Between the `<configuration></configuration>` tags, add the following(don’t add configuration again):
```
<configuration>
   <property>
    <name>hadoop.tmp.dir</name>
    <value>/usr/local/Cellar/hadoop/hdfs/tmp</value>
    <description>A base for other temporary directories.</description>
  </property>
  <property>
    <name>fs.defaultFS</name>
    <value>hdfs://localhost:9010</value>
  </property>
</configuration>
```
This sets up the temporary folder that the hadoop server can use as well as the port as 9010 for the hadoop server.

#### hdfs-site.xml
Open the file core-site.xml. Between the `<configuration></configuration>` tags, add the following(don’t add the configuration tag again):
```
<configuration>
  <property>
    <name>dfs.replication</name>
    <value>1</value>
  </property>
</configuration>
```

This sets up the replication value - a value of 1 means that only one copy of each file in the hadoop file system will be maintained.
In practice, for distributed hadoop file systems, multiple copies are maintained to ensure redundancy for reduced downtime.

#### mapred-site.xml
Open the file mapred-site.xml. Between the `<configuration></configuration>` tags, add the following (don’t add the configuration tag again):
```
<configuration>
  <property>
    <name>mapred.job.tracker</name>
    <value>localhost:9011</value>
  </property>
</configuration>
```

This configures the map-reduce server to run on port 9011.

#### Format the Hadoop file system
With all the configuration done, let's format the hadoop file system for it’s first use. Run the following command:
```
hdfs namenode -format
```

#### Add Shortcuts to start/stop hadoop servers
Add the following entries to the end of file **~/.zshrc**:
```
alias hstart="/hadoop_dir/sbin/start-dfs.sh;/hadoop_dir/sbin/start-yarn.sh"
alias hstop="/hadoop_dir/sbin/stop-yarn.sh;/hadoop_dir/sbin/stop-dfs.sh"
```

While this is strictly optional, this helps start and stop hadoop and yarn servers in the correct order without needing the whole path.

Type the following command to immediately apply the change:
```
source ~/.zshrc
```

### Run Hadoop
We are finally ready to run hadoop now!

Execute the following command
```
hstart
```

Go to the location http://localhost:9870/ on your browser (this is the default namenode location). You should see the information page indicating that the localhost at 9010 port is active. Yarn logs will be available at http://localhost:8088/.

To stop the hadoop server, execute the following command:
```
hstop
```


## IDEs/Code Editors
### Simple text editors(vi/emacs/nano)
These are the most lightweight text file editors that offer no hand holding. While not necessary, it is useful to learn one of these because if you are on a system without any complex editors/GUI/mouse support, these WILL come to your rescue. Also very helpful in assisting with system crashes, low power systems like raspberry pi or if you only have terminal access (a LOT of enterprise and cloud infrastructure).
Be warned though, these do have a steep learning curve. Very useful if you are planning on a career in Software engineering and bragging rights. Install instructions are deliberately not included here to get the reader used to searching online on how to use these.

### Graphical Text editors(VS Code/Sublime/Notepad++)
These are the next level of text editors - they offer GUI and mouse support, autocomplete, indentation, syntax highlighting, file browser, git/svn integration etc. These are more resource heavy than the simple text editors but much less resource intensive than the IDEs mentioned below. You are still on your own w.r.t. Project structures, config files - but these will help you create and manage the files within a single instance of the editor.
Install instructions are widely available online.

### Integrated Development Environments(IntelliJ/eclipse/Visual Studio) 
These are the most resource heavy but also the most integrated solutions. They will load up most of the necessary libraries required for your project and will have skeleton structures for multiple types of projects that will have all necessary files created for the project; you only need to worry about the logic of your project instead of getting into the details of the exact project structure. You can also execute, test, debug and build a deployable without leaving the IDE.

An example would be creating an android based app using Eclipse (with android components installed). Creating a new project will generate ALL the necessary files that the app will need (including permission config files, android based libraries etc.). You can then add the UI and logic to your app, after which the IDE will have the ability to launch an android emulator to test and debug your application. Finally, you can also build the final app and deploy it to the Android marketplace of your choice.

Install instructions are widely available online.

### Browser based REPL - Jupyter
Jupyter aims to bridge the divide between the lightweight text editor and graphical text editor. It uses the browser on your computer to provide a nice graphical and easy to use interface while reducing the resources required. Jupyter really shines in situations where you are performing computing tasks over the network i.e. you are running tasks on a server over a network. 

This does, however, take away a lot of control from the user in an attempt to provide an all round solution and adds hooks into several system locations, making it difficult to un-install.

To install use the command:
```
pip3 install jupyter
```

To configure Jupyter for Python3, open the ‘.zshrc’ file and add the following lines:
```
export PYSPARK_PYTHON=python3
export PYSPARK_DRIVER_PYTHON=python3
export PYSPARK_DRIVER_PYTHON=jupyter
export PYSPARK_DRIVER_PYTHON_OPTS='notebook'
```

After this, run the following command to reload the environment variables:
```
source .zshrc
```

This finishes the Jupyter setup. After this, to start the Jupyter notebook and run your code, use:
```
jupyter notebook
```

This will start the Jupyter notebook in your default browser. You can run the same example code as provided in pyspark setup section to check that Jupyter is working.
