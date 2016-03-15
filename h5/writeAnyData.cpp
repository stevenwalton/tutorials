/*
 * *******************************************************************************************
 * *************************** Created by: Steven Walton *************************************
 * *************************** walton.stevenj@gmail.com  *************************************
 */

#include <iostream>
#include <vector>
#include <string>
#include "H5Cpp.h"


using namespace std;
using namespace H5;

class WriteH5
{
   private:
      string variable;
      string filename;
   public:
      void setFileName(string name) {filename = name;};
      void setVarName(string name) {variable = name;};
      void writeData(vector<int>);
      void writeData(vector<float>);
};

void WriteH5::writeData(vector<int> data)
{
   Exception::dontPrint();

   int npts = data.size();
   int *a = new int[npts];
   int vrank = 1;
   for (size_t i = 0; i < npts; i++)
      a[i] = data[i];
   hsize_t dims[1];
   dims[0] = npts;
   cout << "We have filename: " << filename << endl;
   cout << "data: " << variable << endl;

   const H5std_string FILE_NAME(filename);
   H5std_string DATASET_NAME(variable);
   H5File file(FILE_NAME, H5F_ACC_RDWR);

   DataSpace dsp = DataSpace(vrank,dims);
   DataSet dset = file.createDataSet(DATASET_NAME, PredType::STD_I32BE, dsp);
   dset.write(a, PredType::NATIVE_INT);

   dset.close();
   dsp.close();
   file.close();
   delete[] a;
}

void WriteH5::writeData(vector<float> data)
{
   Exception::dontPrint();

   int npts = data.size();
   float*a = new float[npts];
   int vrank = 1;
   for (size_t i = 0; i < npts; i++)
      a[i] = data[i];
   hsize_t dims[1];
   dims[0] = npts;
   cout << "We have filename: " << filename << endl;
   cout << "data: " << variable << endl;

   const H5std_string FILE_NAME(filename);
   H5std_string DATASET_NAME(variable);
   H5File file(FILE_NAME, H5F_ACC_RDWR);

   DataSpace dsp = DataSpace(vrank,dims);
   DataSet dset = file.createDataSet(DATASET_NAME, PredType::IEEE_F32BE, dsp);
   dset.write(a, PredType::NATIVE_FLOAT);

   dset.close();
   dsp.close();
   file.close();
   delete[] a;
}

int main()
{
   int maxitr = 10;
   vector<int> v;

   for (size_t i = 0; i < maxitr; i++)
      v.push_back(i);
   WriteH5 dta;
   dta.setFileName("testData.h5");
   dta.setVarName("IntData");
   dta.writeData(v);

   vector<float> f;
   for (size_t i = 0; i < maxitr; i++)
      f.push_back(i*0.1);
   dta.setVarName("FloatData");
   dta.writeData(f);
   return 0;
}
