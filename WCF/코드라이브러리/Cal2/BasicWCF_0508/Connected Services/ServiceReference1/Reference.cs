﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace BasicWCF_0508.ServiceReference1 {
    using System.Runtime.Serialization;
    using System;
    
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="ProductInfo", Namespace="http://RuAAService.co.kr/Product")]
    [System.SerializableAttribute()]
    public partial class ProductInfo : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        private int IDField;
        
        private string NameField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string CompanyField;
        
        private double ValueField;
        
        private System.DateTime CreateDateField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]
        public int ID {
            get {
                return this.IDField;
            }
            set {
                if ((this.IDField.Equals(value) != true)) {
                    this.IDField = value;
                    this.RaisePropertyChanged("ID");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]
        public string Name {
            get {
                return this.NameField;
            }
            set {
                if ((object.ReferenceEquals(this.NameField, value) != true)) {
                    this.NameField = value;
                    this.RaisePropertyChanged("Name");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=2)]
        public string Company {
            get {
                return this.CompanyField;
            }
            set {
                if ((object.ReferenceEquals(this.CompanyField, value) != true)) {
                    this.CompanyField = value;
                    this.RaisePropertyChanged("Company");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(IsRequired=true, Order=3)]
        public double Value {
            get {
                return this.ValueField;
            }
            set {
                if ((this.ValueField.Equals(value) != true)) {
                    this.ValueField = value;
                    this.RaisePropertyChanged("Value");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(IsRequired=true, Order=4)]
        public System.DateTime CreateDate {
            get {
                return this.CreateDateField;
            }
            set {
                if ((this.CreateDateField.Equals(value) != true)) {
                    this.CreateDateField = value;
                    this.RaisePropertyChanged("CreateDate");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="ServiceReference1.ICal")]
    public interface ICal {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ICal/GetProduct", ReplyAction="http://tempuri.org/ICal/GetProductResponse")]
        BasicWCF_0508.ServiceReference1.ProductInfo GetProduct();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ICal/GetProduct", ReplyAction="http://tempuri.org/ICal/GetProductResponse")]
        System.Threading.Tasks.Task<BasicWCF_0508.ServiceReference1.ProductInfo> GetProductAsync();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ICal/Add", ReplyAction="http://tempuri.org/ICal/AddResponse")]
        int Add(int a, int b);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ICal/Add", ReplyAction="http://tempuri.org/ICal/AddResponse")]
        System.Threading.Tasks.Task<int> AddAsync(int a, int b);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ICal/Sub", ReplyAction="http://tempuri.org/ICal/SubResponse")]
        int Sub(int a, int b);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ICal/Sub", ReplyAction="http://tempuri.org/ICal/SubResponse")]
        System.Threading.Tasks.Task<int> SubAsync(int a, int b);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ICal/Mul", ReplyAction="http://tempuri.org/ICal/MulResponse")]
        int Mul(int a, int b);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ICal/Mul", ReplyAction="http://tempuri.org/ICal/MulResponse")]
        System.Threading.Tasks.Task<int> MulAsync(int a, int b);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ICal/Div", ReplyAction="http://tempuri.org/ICal/DivResponse")]
        double Div(int a, int b);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/ICal/Div", ReplyAction="http://tempuri.org/ICal/DivResponse")]
        System.Threading.Tasks.Task<double> DivAsync(int a, int b);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public interface ICalChannel : BasicWCF_0508.ServiceReference1.ICal, System.ServiceModel.IClientChannel {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public partial class CalClient : System.ServiceModel.ClientBase<BasicWCF_0508.ServiceReference1.ICal>, BasicWCF_0508.ServiceReference1.ICal {
        
        public CalClient() {
        }
        
        public CalClient(string endpointConfigurationName) : 
                base(endpointConfigurationName) {
        }
        
        public CalClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public CalClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public CalClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress) {
        }
        
        public BasicWCF_0508.ServiceReference1.ProductInfo GetProduct() {
            return base.Channel.GetProduct();
        }
        
        public System.Threading.Tasks.Task<BasicWCF_0508.ServiceReference1.ProductInfo> GetProductAsync() {
            return base.Channel.GetProductAsync();
        }
        
        public int Add(int a, int b) {
            return base.Channel.Add(a, b);
        }
        
        public System.Threading.Tasks.Task<int> AddAsync(int a, int b) {
            return base.Channel.AddAsync(a, b);
        }
        
        public int Sub(int a, int b) {
            return base.Channel.Sub(a, b);
        }
        
        public System.Threading.Tasks.Task<int> SubAsync(int a, int b) {
            return base.Channel.SubAsync(a, b);
        }
        
        public int Mul(int a, int b) {
            return base.Channel.Mul(a, b);
        }
        
        public System.Threading.Tasks.Task<int> MulAsync(int a, int b) {
            return base.Channel.MulAsync(a, b);
        }
        
        public double Div(int a, int b) {
            return base.Channel.Div(a, b);
        }
        
        public System.Threading.Tasks.Task<double> DivAsync(int a, int b) {
            return base.Channel.DivAsync(a, b);
        }
    }
}
