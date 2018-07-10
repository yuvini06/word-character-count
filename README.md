# CO222: Programming Methodology (Project 02)

## Description: 
One of the most important features of any written language is the occurrence of particular characters or words in general. For example, in the English language, all 26 characters are not used in the same frequency. Generally, characters like e, a, t appear more frequently in text. These kinds of information can be used in different applications such as Machine Learning, OCR, Cryptography, etc. The same applies for words. Prepositions and articles like the, a, and, in are more frequently used than other words.
This project allows you to observe this characteristic in the English language using a program. A file or multiple files containing English text will be sent to the program, and the program generates an output (word or character frequencies) as a horizontal bar chart printed on the terminal. 

*A sample output of the program is illustrated in the Output.pdf file*

## Control Arguments for the Program:

- **File name/ File Names** 

The program can accept any number of file names in any order.

- **Number of rows in the chart**

The argument specifies the number of rows in the bar chart. It should be given as -l 10 where 10 is the limit. It can be any positive integer. A number should always follow the -l argument. The pair can be in any place of the arguments list.

- **Scaled option**

When –scaled argument is given, the first row of the graph fully occupies the max print width. Any other row should scale to be matched with first row scale factor.

- **Word/ Character toggle**

The program can analyse two modes of frequencies, characters and words. If the output should be given as words, the -w should be given whereas -c argument will give character frequency output.

- **Default options**

The program must take at least one file name to work. All other arguments are optional. If not given, the program will work as non-scaled, will output frequencies for words and limit the output rows to 10.

- **Pre-processing**

All the non-alphanumeric characters will be removed from the text. For example, the word b@dW0rd is changed into bdW0rd. Then, it should be converted into the lower-case string, and only the processed words will be taken into calculations. While printing, if two words share the same frequency, the first occurred word in the text will be printed first on the chart. Also, all the numbers should have two decimal places only.



