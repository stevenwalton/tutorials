#include <iostream>
#include <string>
#include "H5Cpp.h"

using namespace std;
using namespace H5;

int main()
{
   try
   {
      Exception::dontPrint();
      H5std_string FILE_NAME("data.h5");
      //string variable = "intArray";
      string variable = "fieldVars/T";
      H5File file(FILE_NAME, H5F_ACC_RDONLY);
      DataSet dataset = file.openDataSet(variable);
      DataType datatype = dataset.getDataType();

      // Get the size of the data (type)
      size_t theSize = datatype.getSize();
      cout << "Size: " << theSize << endl;

      // Get the number of dimensions
      DataSpace dataspace = dataset.getSpace();
      const int ndims = dataspace.getSimpleExtentNdims();
      cout << "dims: " << ndims << endl;

      // Get the number of points in the dimension
      const int npts = dataspace.getSimpleExtentNpoints();
      cout << "numpts: " << npts << endl;

      // Is simple?
      bool simp = dataspace.isSimple();
      cout << "Simple: " << simp << endl;

      // Get the type of data inside the dataset
      H5T_class_t classt = datatype.getClass();
      if (classt == 0) { cout << "I32BE" << endl; }
      else if (classt == 1) { cout << "F32BE" << endl;}
      else {cout << "I don't know this data type" << endl;}

      // Protect our memory
      dataspace.close();
      datatype.close();
      dataset.close();
      file.close();
      return 0;
   }
   catch (FileIException error)
   {
      cout << "File not found" << endl;
      //error.printError();
      return 1;
   }
   catch (GroupIException error)
   {
      cout << "Group not found" << endl;
      //error.printError();
      return 1;
   }
   return 0;


}
