using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace maviCafe
{
    public partial class Form1 : Form
    {
        int total_tutar = 0, cay_adet = 0, latte_adet = 0, turk_kahvesi_adet = 0, soguk_ıcecek_adet = 0, limonata_adet = 0, 
            dondurma_adet = 0, tost_adet = 0, patates_adet = 0, hamburger_adet = 0, pasta_adet = 0, cupkek_adet = 0, 
            waffle_adet = 0, cheesecake_adet = 0, profiterol_adet = 0, sutlac_adet = 0;

        int tiklama_sayac = 0, cay_sayac = 0, latte_sayac = 0, turk_kahvesi_sayac = 0, icecek_sayac = 0, limonata_sayac = 0,
            dondurma_sayac = 0, tost_sayac = 0, patates_sayac = 0, hamburger_sayac = 0, pasta_sayac = 0,
            cupcake_sayac = 0, waffle_sayac = 0, cheesecake_sayac = 0, profiterol_sayac = 0, sutlac_sayac = 0;

        bool cay_tiklama = true, latte_tiklama = true, turk_kahvesi_tiklama = true, icecek_tiklama = true, limonata_tiklama = true, 
            dondurma_tiklama = true, tost_tiklama = true, patates_tiklama = true, hamburger_tiklama = true, pasta_tiklama = true, 
            cupcake_tiklama = true, waffle_tiklama = true, cheesecake_tiklama = true, profiterol_tiklama = true, sutlac_tikalama = true;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void cay_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 3;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (cay_tiklama)
            {
                cay_tiklama = false;

                cay_adet = cay_adet + 1;
                urunler.Items.Add("Çay  X" + cay_adet + "  Adet");

                cay_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;

            }
            else
            {
                cay_adet = cay_adet + 1;
                urunler.Items[cay_sayac] = "Çay X" + cay_adet + "  Adet";
            }
            
        }

        private void latte_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 12;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (latte_tiklama)
            {
                latte_tiklama = false;

                latte_adet = latte_adet + 1;
                urunler.Items.Add("Latte X" + latte_adet + " Adet");

                latte_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                latte_adet = latte_adet + 1;
                urunler.Items[latte_sayac] = "Latte X" + latte_adet + " Adet";
            }
        }

        private void turk_kahve_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 10;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (turk_kahvesi_tiklama)
            {
                turk_kahvesi_tiklama = false;

                turk_kahvesi_adet = turk_kahvesi_adet + 1;
                urunler.Items.Add("Türk Kahvesi X" + turk_kahvesi_adet + " Adet");

                turk_kahvesi_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                turk_kahvesi_adet = turk_kahvesi_adet + 1;
                urunler.Items[turk_kahvesi_sayac] = "Türk Kahvesi X" + turk_kahvesi_adet + " Adet";
            }
        }

        private void icecek_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 6;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (icecek_tiklama)
            {
                icecek_tiklama = false;

                soguk_ıcecek_adet = soguk_ıcecek_adet + 1;
                urunler.Items.Add("Soğuk İçecek X" + soguk_ıcecek_adet + " Adet");

                icecek_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                soguk_ıcecek_adet = soguk_ıcecek_adet + 1;
                urunler.Items[icecek_sayac] = "Soğuk İçecek X" + soguk_ıcecek_adet + " Adet";
            }
        }

        private void limonata_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 5;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (limonata_tiklama)
            {
                limonata_tiklama = false;

                limonata_adet = limonata_adet + 1;
                urunler.Items.Add("Limonata X" + limonata_adet + " Adet");

                limonata_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                limonata_adet = limonata_adet + 1;
                urunler.Items[limonata_sayac] = "Limonata X" + limonata_adet + " Adet";
            }
        }

        private void dondurma_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 5;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (dondurma_tiklama)
            {
                dondurma_tiklama = false;

                dondurma_adet = dondurma_adet + 1;
                urunler.Items.Add("Dondurma X" + dondurma_adet + " Adet");

                dondurma_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                dondurma_adet = dondurma_adet + 1;
                urunler.Items[dondurma_sayac] = "Dondurma X" + dondurma_adet + " Adet";
            }
        }

        private void tost_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 7;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (tost_tiklama)
            {
                tost_tiklama = false;

                tost_adet = tost_adet + 1;
                urunler.Items.Add("Tost X" + tost_adet + " Adet");

                tost_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                tost_adet = tost_adet + 1;
                urunler.Items[tost_sayac] = "Tost X" + tost_adet + " Adet";
            }
        }

        private void patates_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 8;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            patates_adet = patates_adet + 1;

            if (patates_tiklama)
            {
                patates_tiklama = false;

                tost_adet = tost_adet + 1;
                urunler.Items.Add("Patates Kızartması X" + patates_adet + " Adet");

                patates_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                tost_adet = tost_adet + 1;
                urunler.Items[patates_sayac] = "Patates Kızartması X" + patates_adet + " Adet";
            }
        }

        private void hamburger_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 22;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (hamburger_tiklama)
            {
                hamburger_tiklama = false;

                hamburger_adet = hamburger_adet + 1;
                urunler.Items.Add("Hamburger X" + hamburger_adet + " Adet");

                hamburger_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                hamburger_adet = hamburger_adet + 1;
                urunler.Items[hamburger_sayac] = "Hamburger X" + hamburger_adet + " Adet";
            }
        }

        private void pasta_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 35;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (pasta_tiklama)
            {
                pasta_tiklama = false;

                pasta_adet = pasta_adet + 1;
                urunler.Items.Add("Pasta X" + pasta_adet + " Adet");

                pasta_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                pasta_adet = pasta_adet + 1;
                urunler.Items[pasta_sayac] = "Pasta X" + pasta_adet + " Adet";
            }
        }

        private void cup_kek_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 10;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (cupcake_tiklama)
            {
                cupcake_tiklama = false;

                cupkek_adet = cupkek_adet + 1;
                urunler.Items.Add("Cup Kek X" + cupkek_adet + " Adet");

                cupcake_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                cupkek_adet = cupkek_adet + 1;
                urunler.Items[cupcake_sayac] = "Cup Kek X" + cupkek_adet + " Adet";
            }
        }

        private void waffle_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 19;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (waffle_tiklama)
            {
                waffle_tiklama = false;

                waffle_adet = waffle_adet + 1;
                urunler.Items.Add("Waffle X" + waffle_adet + " Adet");

                waffle_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                waffle_adet = waffle_adet + 1;
                urunler.Items[waffle_sayac] = "Waffle X" + waffle_adet + " Adet";
            }
        }

        private void cheesecake_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 9;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (cheesecake_tiklama)
            {
                cheesecake_tiklama = false;

                cheesecake_adet = cheesecake_adet + 1;
                urunler.Items.Add("Cheesecake X" + cheesecake_adet + "  Adet");

                cheesecake_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                cheesecake_adet = cheesecake_adet + 1;
                urunler.Items[cheesecake_sayac] = "Cheesecake X" + cheesecake_adet + "  Adet";
            }
        }

        private void profiterol_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 8;

            sonuc_txt.Text = total_tutar + " Türk Lirası";

            if (profiterol_tiklama)
            {
                profiterol_tiklama = false;

                profiterol_adet = profiterol_adet + 1;
                urunler.Items.Add("Profiterol X" + profiterol_adet + " Adet");

                profiterol_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                profiterol_adet = profiterol_adet + 1;
                urunler.Items[profiterol_sayac] = "Profiterol X" + profiterol_adet + " Adet";
            }
        }

        private void sutlac_resim(object sender, EventArgs e)
        {
            total_tutar = total_tutar + 7;

            sonuc_txt.Text = total_tutar + " Türk Lirası";       

            if (sutlac_tikalama)
            {
                sutlac_tikalama = false;

                sutlac_adet = sutlac_adet + 1;
                urunler.Items.Add("Sütlaç X" + sutlac_adet + " Adet");

                sutlac_sayac = tiklama_sayac;
                tiklama_sayac = tiklama_sayac + 1;
            }
            else
            {
                sutlac_adet = sutlac_adet + 1;
                urunler.Items[sutlac_sayac] = "Sütlaç X" + sutlac_adet + " Adet";
            }
        }
    }
}
