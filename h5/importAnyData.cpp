#include <iostream>
#include <vector>
#include <string>
#include "H5Cpp.h"

using namespace std;
using namespace H5;

int main(int argc, char **argv)
{
   try
   {
      Exception::dontPrint();
      if (argc != 2)
      {
         cout << "Must take 2 arguments. h5 file and data to be imported" << endl;
         return 1;
      }
      string name = argv[1];
      string variable = argv[2];
      H5std_string FILE_NAME(name);
      H5File file(FILE_NAME, H5_ACC_RDONLY);
      DataSet dataset = file.openDataSet(variable);
      DataType datatype = dataset.getDataType();

      // Get the number of points
      const int npts = dataspace.getSimpleExtentNpoints();
      // Get data type
      H5T_class_t classt = datatype.getClass();
      if ( classt == 0)
      {
         cout << "I32BE" << endl;
         int *data = new data[npts];
         dataset.read(data, PredType::IEEE_I32BE);
         vector<int> v(data, data + npts);
      }
      else if ( classt == 1)
      {
         cout << "F32BE" << endl;
         float * data = new data[npts];
         dataset.read(data, PredType::IEEE_F32BE);
      }
      delete[] data;
