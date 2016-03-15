/*
 * *******************************************************************************************
 * *************************** Created by: Steven Walton *************************************
 * *************************** walton.stevenj@gmail.com  *************************************
 * *******************************************************************************************
 * This code serves as a skeleton for loading any type of H5 data. In our case we are only
 * looking at STD_INT32BE and IEEE_F32BE as possible import types. With our existing skeleton
 * it is as simple as adding a new function to LoadH5 and the appropriate overload to the Proxy
 * class (see below) to add more data types. 
 * 
 * USAGE: ./importAnyData nameOfFile.h5 nameOfVariable
 * This is example code, and as such it will import only one dataset and then output the
 * first 10 elements, to verify that it is working correctly
 */
#include <iostream>
#include <vector>
#include <string>
#include "H5Cpp.h"

using namespace std;
using namespace H5;

// This class will serve as our data loader. In the main function this will be called to load
// any data from any h5 file
class LoadH5
{
   private:
      string variable;
      string filename;

   public:
      // We have to first create the functions with proper return types
      vector<int> getDataint() const;
      vector<float> getDatafloat() const;
      void setVarName(string var) {variable = var;};
      void setFileName(string path) {filename = path;};

      // We now make a proxy class so that we can overload the return type and use a single
      // function to get data whether int or float. This could be made more advanced by 
      // adding more data types (such as double). 
      class Proxy
      {
         private:
            LoadH5 const* myOwner;
         public:
            Proxy( const LoadH5* owner ) : myOwner( owner ) {}
            operator vector<int>() const
            {
               return myOwner->getDataint();
            }
            operator vector<float>() const
            {
               return myOwner->getDatafloat();
            }
      };
      // Here we use the Proxy class to have a single getData function
      Proxy getData() const {return Proxy(this);}
};


// Our int loading function
vector<int> LoadH5::getDataint() const
{
   H5std_string FILE_NAME(filename);
   H5File file(FILE_NAME, H5F_ACC_RDONLY); // Only reads
   DataSet dataset = file.openDataSet(variable);
   DataType datatype = dataset.getDataType();
   DataSpace dataspace = dataset.getSpace();
   const int npts = dataspace.getSimpleExtentNpoints(); // Gets length of data
   H5T_class_t classt = datatype.getClass(); // Gets the data type of the data
   // Let's make a quick error check
   if ( classt != 0 )
   {
      cout << "This is not an int... you can't save this as an int." << endl;
   }
   int *data = new int[npts]; // allocate at run time what the size will be
   dataset.read(data, PredType::STD_I32BE); // Our standard integer
   vector<int> v(data, data + npts); // Arrays are nice, but vectors are better
   // Manage our memory properly
   delete[] data;
   dataspace.close();
   datatype.close();
   dataset.close();
   file.close();
   return v;
}

// Same as our int function, but with float. Uses IEEE_F32BE
vector<float> LoadH5::getDatafloat() const
{
   H5std_string FILE_NAME(filename);
   H5File file(FILE_NAME, H5F_ACC_RDONLY);
   DataSet dataset = file.openDataSet(variable);
   DataType datatype = dataset.getDataType();
   DataSpace dataspace = dataset.getSpace();
   const int npts = dataspace.getSimpleExtentNpoints();
   H5T_class_t classt = datatype.getClass();
   if ( classt != 1 )
   {
      cout << "This is not a float... you can't save this as a float." << endl;
   }
   float *data = new float[npts];
   dataset.read(data, PredType::IEEE_F32BE);
   vector<float> v(data, data + npts);
   delete[] data;
   dataspace.close();
   datatype.close();
   dataset.close();
   file.close();
   return v;
}


int main(int argc, char **argv)
{
   Exception::dontPrint();
   if (argc != 3)
   {
      cout << "Must take 2 arguments. h5 file and data to be imported" << endl;
      cout << "argc: " << argc << endl;
      return 1;
   }
   string name = argv[1];
   string varname = argv[2];

   LoadH5 dset;
   dset.setFileName(name);
   dset.setVarName(varname);
   vector<float> mydata = dset.getData();
   cout << "I GOT THE DATA" << endl;
   for (size_t i = 0; i < 10; i++)
      cout << mydata[i] << endl;
   return 0;
}
