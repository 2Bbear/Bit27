using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Configuration;
using System.ServiceModel;
namespace FileIOSystemServer_0510
{
    [ServiceContract(SessionMode= SessionMode.Required, CallbackContract = typeof(IFileCallback))]
    interface IFile
    {
        [OperationContract]
        bool UpLoadFile(string name, int idx, string filename, byte[] data);

        [OperationContract(IsOneWay =false, IsInitiating =true, IsTerminating =false)]
        StudentData[] Join(string name, int idx);

        [OperationContract(IsOneWay = true, IsInitiating = false, IsTerminating = true)]
        void Leave(string name, int idx);

    }

    interface IFileCallback
    {
        [OperationContract(IsOneWay = true)]
        void FileRecive(string name, int idx, string msg, byte[] filedata);
        [OperationContract(IsOneWay = true)]
        void UserEnter(string name, int idx);
        [OperationContract(IsOneWay = true)]
        void UserLeave(string name, int idx);

    }
}
