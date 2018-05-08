using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using BasicWCF_0508.ServiceReference2;

namespace BasicWCF_0508
{
    public partial class Form1 : Form
    {
        //접속을 위한 객체
        public BankClient bank = new BankClient();

        //생성되는 어카운트들을 담을 리스트
        public List<AccountInfo> accountlist = new List<AccountInfo>();



        public Form1()
        {
            InitializeComponent();
        }
        #region 컨트롤 이벤트
        //계정 생성
        private void Account_ClickButton(object sender, EventArgs e)
        {
            AccountInfo temp = bank.GetProduct(int.Parse(textBox1.Text), textBox3.Text);
            temp.Balance = int.Parse(textBox2.Text);

            accountlist.Add(temp);

            //계정 정보 출력
            AccountPrint(temp.ID, temp.Balance, temp.AccountName, temp.AccountDate);

            //리스트에 갱신
            OutputAccountListItem();

        }

        //입금
        private void Diposit_ClickButton(object sender, EventArgs e)
        {
            int targetIdx = SearchAccountOutIdx(int.Parse(comboBox1.SelectedItem.ToString()));
            if (targetIdx==-1)
            {
                MessageBox.Show("해당 계정을 찾지 못했습니다.");
            }

            if(bank.AddMoney(accountlist[targetIdx], int.Parse(textBox8.Text)))
            {
                accountlist[targetIdx].Balance += int.Parse(textBox8.Text);
            }

            AccountPrint(accountlist[targetIdx].ID, accountlist[targetIdx].Balance, accountlist[targetIdx].AccountName, accountlist[targetIdx].AccountDate);


        }
        //출금
        private void Withdrow_ClickButton(object sender, EventArgs e)
        {
            int targetIdx = SearchAccountOutIdx(int.Parse(comboBox1.SelectedItem.ToString()));
            if (targetIdx == -1)
            {
                MessageBox.Show("해당 계정을 찾지 못했습니다.");
            }

            if (bank.MinMoney(accountlist[targetIdx], int.Parse(textBox8.Text)))
            {
                accountlist[targetIdx].Balance -= int.Parse(textBox8.Text);
            }
            else
            {
                MessageBox.Show("출금오류.");
            }

            AccountPrint(accountlist[targetIdx].ID, accountlist[targetIdx].Balance, accountlist[targetIdx].AccountName, accountlist[targetIdx].AccountDate);

        }

        #endregion

        #region 내부 소스
        //계정 검색
        private int SearchAccountOutIdx(int _id)
        {
            for(int i=0; i< accountlist.Count; i++)
            {
                if(accountlist[i].ID==_id)
                {
                    return i;
                }
            }
            return -1;
        }

        //계정 정보 출력
        private void AccountPrint(int _id, int _bal, string _name, DateTime _date)
        {
            //Control clear

            //id
            textBox4.Text = _id.ToString();
            //bal
            textBox5.Text = _bal.ToString();
            //name
            textBox6.Text = _name;
            //date
            textBox7.Text = _date.ToString();
        }

        //listBoxControl Item 출력
        private void OutputAccountListItem()
        {
            //list initialize
            comboBox1.Items.Clear();

            foreach(AccountInfo t in accountlist)
            {
                comboBox1.Items.Add(t.ID);
            }
        }

        #endregion
        
    }

}
