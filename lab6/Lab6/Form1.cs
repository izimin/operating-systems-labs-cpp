using System;
using System.Threading;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Laba6
{
    public partial class Form1 : Form
    {
        Dictionary<int, ThreadData> threads = new Dictionary<int, ThreadData>();
        //Mutex mutex = new Mutex();
        Random rand = new Random();
        object locker = new object();
        int delay = 10;

        public Form1()
        {
            InitializeComponent();
            //this.KeyPreview = true;
        }

        //private void Form1_KeyDown(object sender, KeyEventArgs e)
        //{
        //    if (e.KeyCode == Keys.F1 )
        //    {
        //         CreateThread.PerformClick();  // имитируем нажатие button1
        //    }

        //    if (e.KeyCode == Keys.Delete)
        //    {
        //        StopThread.PerformClick();
        //    }
        //}

        // Обработка клика на клавишу "Создать поток"
        private void CreateThread_Click(object sender, EventArgs e)
        {
            int indexThread = 0;

            // Ищем свободный индекс в нашей коллекции
            for (indexThread = 0; indexThread < int.MaxValue; indexThread++)
                if (!threads.ContainsKey(indexThread)) break;

            // Добавляем в комбобокс потоков создаваемый поток 
            string num = (indexThread + 1) < 10 ? "0" + (indexThread + 1).ToString() : (indexThread + 1).ToString();
            ComboBoxThreads.Items.Add("Поток " + num);
            ComboBoxThreads.Sorted = true;
            threads.Add(indexThread, new ThreadData(new Thread(() => WorkThread(indexThread))));

            // Включаем кнопки завершения потока и изменения различных хаврактеристик
            if (ComboBoxThreads.Items.Count == 1)
                AccessToButtons(true);

            // Выбираем в комбобоксе созданый поток текущим 
            ComboBoxThreads.SelectedIndex++;

            // Запускаем поток
            threads[indexThread].Thread.Start();
        } 

        // Делигат работы потока 
        void WorkThread(int indexTread)
        {
            // Для выхода из цикла, когда поток стаёт не активным
            var isActivity = threads[indexTread].Status;
            
            while (isActivity)
            {
                // Начало критической секции 
                lock (locker)
                {
                    Thread.Sleep((10 - delay) * 4);
                    var x = rand.Next(0, pictureBox1.Width);
                    var y = rand.Next(0, pictureBox1.Height);
                    var brush = new SolidBrush(threads[indexTread].CircleColor);
                    var radius = threads[indexTread].CircleRadius;
                    pictureBox1.CreateGraphics().FillEllipse(brush, x, y, radius, radius);
                    isActivity = threads[indexTread].Status;
                }
            }
        }

        // Обработка нажатия на клавишу "Завершить поток"
        private void StopThread_Click(object sender, EventArgs e)
        {
            var indexThread = GetIndex();
            var selectIndex = ComboBoxThreads.SelectedIndex;

            JoinThread(indexThread);
            threads.Remove(indexThread);    
            ComboBoxThreads.Items.RemoveAt(selectIndex);

            if (threads.Count == 0)
            {
                AccessToButtons(false);
            }
            // При удалении потока делаем в списке текущим предыдущий
            else ComboBoxThreads.SelectedIndex = selectIndex  > ComboBoxThreads.Items.Count ? selectIndex : selectIndex - 1;
        }

        // Изменения приоритета 
        private void ComboBoxPriority_SelectedIndexChanged(object sender, EventArgs e)
        {
            var indexThread = GetIndex();

            // Блокируем доступ другим потокам 
            lock (locker)
            {
                threads[indexThread].Thread.Priority = (ThreadPriority)(4 - ComboBoxPriority.SelectedIndex);
            }
        }

        // Обработка изменения комбобокса со списком потоков
        private void ComboBoxThreads_SelectedIndexChanged(object sender, EventArgs e)
        {
            var indexThread = GetIndex();
            ComboBoxPriority.SelectedIndex = (int)threads[indexThread].Thread.Priority;
            numericUpDown1.Value = threads[indexThread].CircleRadius;
            ColorDialog.BackColor = threads[indexThread].CircleColor;
            colorDialog1.Color = threads[indexThread].CircleColor;
        }

        // Изменение цыета кржка
        private void ColorDialog_Click(object sender, EventArgs e)
        {
            var indexThread = GetIndex();

            if (colorDialog1.ShowDialog() != DialogResult.OK) return;
            ColorDialog.BackColor = colorDialog1.Color;

            // Блокируем доступ другим потокам 
            lock (locker)
            {
                threads[indexThread].CircleColor = colorDialog1.Color;
            }
        }

        // Изменение радиуча кружка
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            var indexThread = GetIndex();
         
            // Блокируем доступ другим потокам 
            lock (locker)
            {
                threads[indexThread].CircleRadius = (int)numericUpDown1.Value;
            }
        }

        // Обработка закрытия окна
        protected override void OnClosed(EventArgs e)
        {      
            if (threads.Count <= 0) return;
            foreach (var elements in threads)
            {
                JoinThread(elements.Key);
            }
            threads.Clear();
        }

        void JoinThread(int indexThread)
        {
            // Блокируем доступ другим потокам 
            lock (locker)
            {
                threads[indexThread].Status = false;
            }

            threads[indexThread].Thread.Join();
        }
        
        // Получаем ключ потока, текущего в комбобоксе
        int GetIndex()
        {
            if (ComboBoxThreads.SelectedIndex == -1) return -1;
            return int.Parse(ComboBoxThreads.SelectedItem.ToString().Split(' ')[1]) - 1;                                                                                                     //threads.Keys.ElementAt(ComboBoxThreads.SelectedIndex);
        }

        // Регулирует доступ к кнопкам во время когда потоков не существует блокируем все кнопки, кроме "Создать поток"
        void AccessToButtons (bool value)
        {
            StopThread.Enabled = value;
            numericUpDown1.Enabled = value;
            ColorDialog.Enabled = value;
            StopThread.Enabled = value;
            speedThread.Enabled = value;
        }

        private void speedThread_Scroll(object sender, EventArgs e)
        {
            delay = speedThread.Value;
        }      
    }

    public class ThreadData
    {
        // Сам поток
        Thread thread;
        bool status;

        // Поля для информации о круге
        int circleRadius;
        Color circleColor;

        public ThreadData(Thread t) 
        {
            thread = t;
            status = true;
            circleColor = Color.Black;
            circleRadius = 30;
        }

        public Thread Thread
        {
            get { return thread; }
            set { thread = value; }
        }

        public bool Status
        {
            get { return status; }
            set { status = value; }
        }

        public int CircleRadius
        {
            get { return circleRadius; }
            set { circleRadius = value; }
        }

        public Color CircleColor
        {
            get { return circleColor; }
            set { circleColor = value; }
        }
    }
}
