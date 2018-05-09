using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
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
    



        public Form1()
        {
            InitializeComponent();
            if(bank.ConnectDB().Equals("데이터베이스 연결 실패"))
            {
                
                MessageBox.Show("데이터베이스 연결 실패");
                this.Close();
            }
            MessageBox.Show("데이터베이스 연결 성공");

            
            //타이틀 출력
            Timer titleTimer = new Timer();
            titleTimer.Tick += new EventHandler(TitlePrint);
            titleTimer.Interval = 1000;
            titleTimer.Start();


        }
        void TitlePrint(object sender, EventArgs ea)
        {
            try
            {
                int d = 0;
                d = bank.GetAccCount();
                if (d != 0)
                {
                    this.Text = "현재 저장된 계좌 :" + d + "개";
                }
            }
            catch (Exception ex)
            {
                
            }
            finally
            {
            }
           
            
        }
        #region 컨트롤 이벤트
        //계정 생성
        private void Account_ClickButton(object sender, EventArgs e)
        {
            AccountInfo tt= new AccountInfo { ID = 0, Balance = int.Parse(textBox2.Text), AccountName = textBox3.Text, AccountDate = DateTime.Now };
           
            if (bank.MakeAccount(tt))
            {
                MessageBox.Show("계정 생성 성공");
            }
            else
            {
                MessageBox.Show("계정 생성 실패");
            }


            //계정 정보 출력
            //AccountPrint(temp.ID, temp.Balance, temp.AccountName, temp.AccountDate);

            //리스트에 갱신
            //OutputAccountListItem();

        }

        //입금
        private void Diposit_ClickButton(object sender, EventArgs e)
        {
            if(bank.InputMoney(int.Parse(textBox9.Text),int.Parse(textBox8.Text)))
            {
                MessageBox.Show("입금에 성공했습니다.");
            }
            else
            {
                MessageBox.Show("입금에 실패했습니다.");
            }

        }
        //출금
        private void Withdrow_ClickButton(object sender, EventArgs e)
        {
            if (bank.OutputMoney(int.Parse(textBox9.Text), int.Parse(textBox8.Text)))
            {
                MessageBox.Show("출금에 성공했습니다.");
            }
            else
            {
                MessageBox.Show("출금에 실패했습니다.");
            }
            

        }

        #endregion

        #region 내부 소스
        //계정 검색
        private int SearchAccountOutIdx(int _id)
        {
            //for(int i=0; i< accountlist.Count; i++)
            //{
            //    if(accountlist[i].ID==_id)
            //    {
            //        return i;
            //    }
            //}
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
            ////list initialize
            //comboBox1.Items.Clear();

            //foreach(AccountInfo t in accountlist)
            //{
            //    comboBox1.Items.Add(t.ID);
            //}
        }

        #endregion

        private void AccountDelete_ClickButton(object sender, EventArgs e)
        {
            if(bank.DeleteAccount(int.Parse(textBox1.Text)))
            {
                MessageBox.Show("계정 삭제 성공");
            }
            else
            {
                MessageBox.Show("계정 삭제 실패");
            }
        }

        private void SearchAccount_ClickButton(object sender, EventArgs e)
        {
           AccountInfo temp= bank.SelectAccount(int.Parse(textBox10.Text));

            textBox4.Text = temp.ID.ToString();
            textBox5.Text = temp.Balance.ToString();
            textBox6.Text = temp.AccountName;
            textBox7.Text = temp.AccountDate.ToString();


        }

        private void button6_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
           List<AccountInfo> ttt= bank.SelectAllAccount().ToList<AccountInfo>();
            foreach(AccountInfo t in ttt)
            {
                listBox1.Items.Add(t.AccountName);
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            listBox2.Items.Clear();
            List<AccountList> ttt = bank.SelectAccountList(int.Parse(textBox11.Text)).ToList<AccountList>();
            foreach (AccountList t in ttt)
            {
                listBox2.Items.Add(t.AccID);
            }
        }
    }

}
