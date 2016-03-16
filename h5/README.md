# H5 Tutorials
---------------
This will primarily focus around C++ code. If you are struggling with the documentation online, I hope I can help.

### H5dump errors
-----------------
h5dump does not always seem to output to the standard output (your screen) the stored values. Don't worry as long
as you are loading the correct data type then you will get it. In our case we only work with a 32LE int (my NATIVE INT)
and the IEEE standard for float 32. 

## getDataTypeh5 
-----------------
This code goes through how to get simple information from h5 files without the use of `h5dump`. Information here 
can be used for error checking or to load arrays dynamically and without knowing the actual size and type of 
data that is stored in the file. All you need to know are the headers.

## writeAnyData
---------------
This code shows an example of how to write either float or int data with a single command. We overload the 
`writeData` command so that it can take in either a integer vector or a float vector. Modify for other storage
types. This only uses 32 bit long integers and the IEEE standard for 32 bit floats. 

## importAnyData
----------------
Here we overload a return type by using a Proxy class. This allows us to read in either a 32LE int or an IEEE
32B float with a single function. Note that you will have to change the vector from int to float or vise versa
to load the proper data. 

## PredType
-------------
[Here](https://www.hdfgroup.org/HDF5/doc/RM/PredefDTypes.html) is a link to the Predefined Datatypes that H5 offers
