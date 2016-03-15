#include <iostream>
#include <vector>
#include <string>
#include "H5Cpp.h"

using namespace std;
using namespace H5;

class getDemFiles
{
   private:
      string variable;
      string filename;

   public:
      //getDemFiles;
      vector<int> getDataint() const;
      vector<float> getDatafloat() const;
      void getVar(string var) {variable = var;};

      void fileName(string path) {filename = path;};
      class Proxy
      {
         private:
            getDemFiles const* myOwner;
         public:
            Proxy( const getDemFiles* owner ) : myOwner( owner ) {}
            operator vector<int>() const
            {
               return myOwner->getDataint();
            }
            operator vector<float>() const
            {
               return myOwner->getDatafloat();
            }
      };
      Proxy getData() const {return Proxy(this);}

};


vector<int> getDemFiles::getDataint() const
{
   H5std_string FILE_NAME(filename);
   H5File file(FILE_NAME, H5F_ACC_RDONLY);
   DataSet dataset = file.openDataSet(variable);
   DataType datatype = dataset.getDataType();
   DataSpace dataspace = dataset.getSpace();
   const int npts = dataspace.getSimpleExtentNpoints();
   H5T_class_t classt = datatype.getClass();
   if ( classt != 0 )
   {
      cout << "This is not an int... you can't save this as an int." << endl;
   }
   int *data = new int[npts];
   dataset.read(data, PredType::STD_I32BE);
   vector<int> v(data, data + npts);
   delete[] data;
   dataspace.close();
   datatype.close();
   dataset.close();
   file.close();
   return v;
}

vector<float> getDemFiles::getDatafloat() const
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

   getDemFiles dset;
   dset.fileName(name);
   dset.getVar(varname);
   vector<float> mydata = dset.getData();
   cout << "I GOT THE DATA" << endl;
   for (size_t i = 0; i < 10; i++)
      cout << mydata[i] << endl;
   return 0;
}
