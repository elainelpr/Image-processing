#include<iostream>
#include<opencv2/opencv.hpp>
#define row 480
#define col 640
using namespace std;
using namespace cv;

//Guassian filter
void Gaussin_filter_up(double *a, double* c, int ori_row, int ori_col, double *b)
{
    int i, j;
    for (i = 0; i < ori_row + 4; i++)
    {
        for (j = 0; j < ori_col + 4; j++)
        {
            if (i == 0)  b[i*(ori_col + 4) + j] = 0;
            else if (i == 1)b[i*(ori_col + 4) + j] = 0;
            else if (i == ori_row + 1) b[i*(ori_col + 4) + j] = 0;
            else if (i == ori_row + 2) b[i*(ori_col + 4) + j] = 0;
            else if (j == 0) b[i*(ori_col + 4) + j] = 0;
            else if (j == 1) b[i*(ori_col + 4) + j] = 0;
            else if (j == ori_col + 1) b[i*(ori_col + 4) + j] = 0;
            else if (j == ori_col + 2) b[i*(ori_col + 4) + j] = 0;
            else b[i*(ori_col + 4) + j] = a[(i - 2)*ori_col + (j - 2)];

        }

    }
    for (i = 2; i < ori_row + 2; i++)
    {
        for (j = 2; j < ori_col + 2; j++)
        {

            c[(i - 2)*ori_col + j - 2] = (b[(i - 2)*(ori_col + 4) + j - 2] + b[(i - 2) * (ori_col + 4) + (j + 2)] + b[(i + 2) * (ori_col + 4) + (j - 2)] + b[(i + 2) * (ori_col + 4) + (j + 2)]) * 1 / 256 + (b[(i - 2) * (ori_col + 4) + (j - 1)] + b[(i - 2) * (ori_col + 4) + (j + 1)] + b[(i - 1) * (ori_col + 4) + (j - 2)] + b[(i - 1) * (ori_col + 4) + (j + 2)] + b[(i + 1) * (ori_col + 4) + (j - 2)] + b[(i + 1)*(ori_col + 4) + (j + 2)] + b[(i + 2) * (ori_col + 4) + (j - 1)] + b[(i + 2) * (ori_col + 4) + (j + 1)]) * 4 / 256 + (b[(i - 2) * (ori_col + 4) + j] + b[i * (ori_col + 4) + (j - 2)] + b[i * (ori_col + 4) + (j + 2)] + b[(i + 2) * (ori_col + 4) + j]) * 6 / 256
                + (b[(i - 1) * (ori_col + 4) + (j - 1)] + b[(i - 1) * (ori_col + 4) + (j + 1)] + b[(i + 1) * (ori_col + 4) + (j - 1)] + b[(i + 1) * (ori_col + 4) + (j + 1)]) * 16 / 256 + (b[(i - 1) * (ori_col + 4) + j] + b[i * (ori_col + 4) + (j - 1)] + b[i * (ori_col + 4) + (j + 1)] + b[(i + 1) * (ori_col + 4) + j]) * 24 / 256 + b[i * (ori_col + 4) + j] * 36 / 256;
        }

    }
}

//down sampling, delete even cols and rows
void up_sample_even(double* XF, double* up_sample, int filter_rows, int filter_cols)
{
    int m, n;
    int filter_r0 = 0;
    int filter_c0 = 0;
    for (m = 0; m < 0.5*filter_rows; m++)
    {
        for (n = 0; n < filter_cols*0.5; n++)
        {
            if (m == 0) filter_r0 = 0;
            else filter_r0 = m;
            if (n == 0) filter_c0 = 0;
            else filter_c0 = n;
            up_sample[m*(filter_cols / 2) + n] = XF[(m + filter_r0)*filter_cols + (n + filter_c0)];

        }
    }

}

void down_sample(double* down_sample, double* up_sample, int down_sample_row, int down_sample_col, int up_sample_row, int up_sample_col)
{
    down_sample[down_sample_row*down_sample_col + down_sample_col] = {};
    int i, j;
    for (i = 0; i < up_sample_row; i++)
    {
        for (j = 0; j < up_sample_col; j++)
        {
            down_sample[2 * i*down_sample_col + 2 * j] = up_sample[i*up_sample_col + j];
        }
    }
    
    for (int m = 0; m < down_sample_row; m++)
    {
        for (int n = 0; n < down_sample_col; n++)
        {
            down_sample[m*down_sample_col + n];
        }

    }
}

void Gaussin_filter_down(double *down_sample, double* c_down, int down_row, int down_col, double *b_down)
{
    int i, j;
    for (i = 0; i < down_row + 4; i++)
    {
        for (j = 0; j < down_col + 4; j++)
        {
            if (i == 0)  b_down[i*(down_col + 4) + j] = 0;
            else if (i == 1)  b_down[i*(down_col + 4) + j] = 0;
            else if (i == down_row + 1) b_down[i*(down_col + 4) + j] = 0;
            else if (i == down_row + 2) b_down[i*(down_col + 4) + j] = 0;
            else if (j == 0) b_down[i*(down_col + 4) + j] = 0;
            else if (j == 1) b_down[i*(down_col + 4) + j] = 0;
            else if (j == down_col + 1) b_down[i*(down_col + 4) + j] = 0;
            else if (j == down_col + 2) b_down[i*(down_col + 4) + j] = 0;
            else b_down[i*(down_col + 4) + j] = down_sample[(i - 2)*down_col + (j - 2)];
        }

    }
    for (i = 2; i < down_row + 2; i++)
    {
        for (j = 2; j < down_col + 2; j++)
        {
            c_down[(i - 2)*down_col + j - 2] = (b_down[(i - 2)*(down_col + 4) + j - 2] + b_down[(i - 2) * (down_col + 4) + (j + 2)] + b_down[(i + 2) * (down_col + 4) + (j - 2)] + b_down[(i + 2) * (down_col + 4) + (j + 2)]) * 4 * 1 / 256 + (b_down[(i - 2) * (down_col + 4) + (j - 1)] + b_down[(i - 2) * (down_col + 4) + (j + 1)] + b_down[(i - 1) * (down_col + 4) + (j - 2)] + b_down[(i - 1) * (down_col + 4) + (j + 2)] + b_down[(i + 1) * (down_col + 4) + (j - 2)] + b_down[(i + 1)*(down_col + 4) + (j + 2)] + b_down[(i + 2) * (down_col + 4) + (j - 1)] + b_down[(i + 2) * (down_col + 4) + (j + 1)]) * 4 * 4 / 256 + (b_down[(i - 2) * (down_col + 4) + j] + b_down[i * (down_col + 4) + (j - 2)] + b_down[i * (down_col + 4) + (j + 2)] + b_down[(i + 2) * (down_col + 4) + j]) * 4 * 6 / 256
                + (b_down[(i - 1) * (down_col + 4) + (j - 1)] + b_down[(i - 1) * (down_col + 4) + (j + 1)] + b_down[(i + 1) * (down_col + 4) + (j - 1)] + b_down[(i + 1) * (down_col + 4) + (j + 1)]) * 4 * 16 / 256 + (b_down[(i - 1) * (down_col + 4) + j] + b_down[i * (down_col + 4) + (j - 1)] + b_down[i * (down_col + 4) + (j + 1)] + b_down[(i + 1) * (down_col + 4) + j]) * 4 * 24 / 256 + b_down[i * (down_col + 4) + j] * 4 * 36 / 256;
        }
    }

}

void lp_pyrmid(double *Gaussin_pic, double *down_sample_filter, int down_row, int down_col, double *lp_pic)
{
    for (int i = 0; i < down_row; i++)
    {
        for (int j = 0; j < down_col; j++)
        {
            lp_pic[i*down_col + j] = Gaussin_pic[i*down_col + j] - down_sample_filter[i*down_col + j];
            if (lp_pic[i*down_col + j] < 0) lp_pic[i*down_col + j] = 0;
            if (lp_pic[i*down_col + j] > 255) lp_pic[i*down_col + j] = 255;
        }
    }
}

void AddWeighted(double *lppyrmid1,double alpha, double *lppyrmid2, double beta, double gamma,double *output_dst,int down_row2,int down_col2)
{
    for (int i = 0; i < down_row2; i++)
    {
        for (int j = 0; j < down_col2; j++)
        {
            output_dst[i*down_col2 + j] = lppyrmid1[i*down_col2 + j] * alpha + lppyrmid2[i*down_col2 + j] * beta + gamma;
        }
    }
}

void Add(double *fusion_down_filter,double *lppyrmid, double *output_dst, int down_row2, int down_col2)
{
    for (int i = 0; i < down_row2; i++)
    {
        for (int j = 0; j < down_col2; j++)
        {
            output_dst[i*down_col2 + j] = fusion_down_filter[i*down_col2 + j]+ lppyrmid[i*down_col2 + j];
        }
    }
}

int main()
{
    // Read a image
    Mat a = imread("IR_helib.bmp");
    uchar data_out1[(row/4)*(col/4) * 3];
    //uchar data_out2[row*col * 3];
    Mat img;
    resize(a, img, Size(col, row));
    static double BF[row*col], GF[row*col], RF[row*col];
    static double B[row*col], G[row*col], R[row*col];
    static double b[(row + 4)*(col + 4)];
    static double up_sample1_1[(row / 2)*(col / 2)], up_sample1_2[(row / 2)*(col / 2)], up_sample1_3[(row / 2)*(col / 2)];
    static double up_sample2_1[(row/4)*(col/4)], up_sample2_2[(row / 4)*(col / 4)], up_sample2_3[(row / 4)*(col / 4)];
    static double up_sample3_1[(row / 8)*(col / 8)], up_sample3_2[(row / 8)*(col / 8)], up_sample3_3[(row / 8)*(col / 8)];
    static double down_sample1_1[row*col], down_sample1_2[row*col], down_sample1_3[row*col];
    static double down_sample_filter1_1[row*col], down_sample_filter1_2[row*col], down_sample_filter1_3[row*col];
    static double down_sample2_1[row / 2 * col / 2], down_sample2_2[row / 2 * col / 2], down_sample2_3[row / 2 * col / 2];
    static double down_sample_filter2_1[row / 2 * col / 2], down_sample_filter2_2[row / 2 * col / 2], down_sample_filter2_3[row / 2 * col / 2];
    static double down_sample3_1[row / 4 * col / 4], down_sample3_2[row / 4 * col / 4], down_sample3_3[row / 4 * col / 4];
    static double down_sample_filter3_1[row / 4 * col / 4], down_sample_filter3_2[row / 4 * col / 4], down_sample_filter3_3[row / 4 * col / 4];
    static double lp1_1[row*col], lp1_2[row*col], lp1_3[row*col];
    static double lp2_1[(row/2)*(col/2)], lp2_2[(row / 2)*(col / 2)], lp2_3[(row / 2)*(col / 2)];
    static double lp3_1[(row / 4)*(col / 4)], lp3_2[(row / 4)*(col / 4)], lp3_3[(row / 4)*(col / 4)];
    int rowNumber = img.rows;    //rows
    int colNumber = img.cols * 3;// img.channels();   //cols * number of channels = number of elements each row

    for (int i = 0; i < img.rows; i++)
    {
        //get address from i rows, data points to the first value, type: uchar
        uchar* data = img.ptr<uchar>(i);
        
        for (int j = 0; j < colNumber; j++)
        {
            //extract three channels,R,G,B
            if (j % 3 == 0) B[i * col + (int)(j / 3)] = data[j];
            if (j % 3 == 1) G[i * col + (int)(j / 3)] = data[j];
            if (j % 3 == 2) R[i * col + (int)(j / 3)] = data[j];
        }
    }
    //first layer of Guassin layer
    Gaussin_filter_up(B, BF, row, col, b);//Guassin filter
    Gaussin_filter_up(G, GF, row, col, b);
    Gaussin_filter_up(R, RF, row, col, b);
    up_sample_even(BF, up_sample1_1, row, col);
    up_sample_even(GF, up_sample1_2, row, col);
    up_sample_even(RF, up_sample1_3, row, col);
    //second layer of Guassin layer
    Gaussin_filter_up(up_sample1_1, BF, row/2, col/2, b);
    Gaussin_filter_up(up_sample1_2, GF, row/2, col/2, b);
    Gaussin_filter_up(up_sample1_3, RF, row/2, col/2, b);
    up_sample_even(BF, up_sample2_1, row/2, col/2);
    up_sample_even(GF, up_sample2_2, row/2, col/2);
    up_sample_even(RF, up_sample2_3, row/2, col/2);
    //Third layer of Guassin layer
    Gaussin_filter_up(up_sample2_1, BF, row/4, col/4, b);
    Gaussin_filter_up(up_sample2_2, GF, row/4, col/4, b);
    Gaussin_filter_up(up_sample2_3, RF, row/4, col/4, b);
    up_sample_even(BF, up_sample3_1, row/4, col/4);
    up_sample_even(GF, up_sample3_2, row/4, col/4);
    up_sample_even(RF, up_sample3_3, row/4, col/4);
    //O layer : laplace pyramid
    down_sample(down_sample1_1, up_sample1_1, row, col, row / 2, col / 2);
    down_sample(down_sample1_2, up_sample1_2, row, col, row / 2, col / 2);
    down_sample(down_sample1_3, up_sample1_3, row, col, row / 2, col / 2);
    Gaussin_filter_down(down_sample1_1, down_sample_filter1_1, row, col, b);
    Gaussin_filter_down(down_sample1_2, down_sample_filter1_2, row, col, b);
    Gaussin_filter_down(down_sample1_3, down_sample_filter1_3, row, col, b);
    lp_pyrmid(B, down_sample_filter1_1, row, col, lp1_1);
    lp_pyrmid(G, down_sample_filter1_2, row, col, lp1_2);
    lp_pyrmid(R, down_sample_filter1_3, row, col, lp1_3);
    //first layer : laplace pyramid
    //upsampling, add 0 in even rows and cols
    down_sample(down_sample2_1, up_sample2_1, row/2, col/2, row / 4, col / 4);
    down_sample(down_sample2_2, up_sample2_2, row/2, col/2, row / 4, col / 4);
    down_sample(down_sample2_3, up_sample2_3, row/2, col/2, row / 4, col / 4);
    //Guassin filter
    Gaussin_filter_down(down_sample2_1, down_sample_filter2_1, row/2, col/2, b);
    Gaussin_filter_down(down_sample2_2, down_sample_filter2_2, row/2, col/2, b);
    Gaussin_filter_down(down_sample2_3, down_sample_filter2_3, row/2, col/2, b);
    //generate lapalce pyramid
    lp_pyrmid(up_sample1_1, down_sample_filter2_1, row/2, col/2, lp2_1);
    lp_pyrmid(up_sample1_2, down_sample_filter2_2, row/2, col/2, lp2_2);
    lp_pyrmid(up_sample1_3, down_sample_filter2_3, row/2, col/2, lp2_3);
    //Second layer : laplace pyramid
    down_sample(down_sample3_1, up_sample3_1, row /4, col / 4, row / 8, col / 8);
    down_sample(down_sample3_2, up_sample3_2, row / 4, col / 4, row / 8, col / 8);
    down_sample(down_sample3_3, up_sample3_3, row / 4, col / 4, row / 8, col / 8);
    Gaussin_filter_down(down_sample3_1, down_sample_filter3_1, row / 4, col / 4, b);
    Gaussin_filter_down(down_sample3_2, down_sample_filter3_2, row / 4, col / 4, b);
    Gaussin_filter_down(down_sample3_3, down_sample_filter3_3, row / 4, col / 4, b);
    lp_pyrmid(up_sample2_1, down_sample_filter3_1, row / 4, col / 4, lp3_1);
    lp_pyrmid(up_sample2_2, down_sample_filter3_2, row / 4, col / 4, lp3_2);
    lp_pyrmid(up_sample2_3, down_sample_filter3_3, row / 4, col / 4, lp3_3);

    // imread another image
    Mat m = imread("VIS_helib.bmp");
    //uchar data_out2[(row/2)*(col/2) * 3];
    uchar data_out2[(row)*(col) * 3];
    //uchar data_out2[(row/4)*(col/4) * 3];
    //uchar data_out2[row*col * 3];
    Mat img2;
    resize(m, img2, Size(col, row));
    static double BF2[row*col], GF2[row*col], RF2[row*col];
    static double B2[row*col], G2[row*col], R2[row*col];
    static double b2[(row + 4)*(col + 4)];
    static double up_sample1_1_2[(row / 2)*(col / 2)], up_sample1_2_2[(row / 2)*(col / 2)], up_sample1_3_2[(row / 2)*(col / 2)];
    static double up_sample2_1_2[(row / 4)*(col / 4)], up_sample2_2_2[(row / 4)*(col / 4)], up_sample2_3_2[(row / 4)*(col / 4)];
    static double up_sample3_1_2[(row / 8)*(col / 8)], up_sample3_2_2[(row / 8)*(col / 8)], up_sample3_3_2[(row / 8)*(col / 8)];
    static double down_sample1_1_2[row*col], down_sample1_2_2[row*col], down_sample1_3_2[row*col];
    static double down_sample_filter1_1_2[row*col], down_sample_filter1_2_2[row*col], down_sample_filter1_3_2[row*col];
    static double down_sample2_1_2[row / 2 * col / 2], down_sample2_2_2[row / 2 * col / 2], down_sample2_3_2[row / 2 * col / 2];
    static double down_sample_filter2_1_2[row / 2 * col / 2], down_sample_filter2_2_2[row / 2 * col / 2], down_sample_filter2_3_2[row / 2 * col / 2];
    static double down_sample3_1_2[row / 4 * col / 4], down_sample3_2_2[row / 4 * col / 4], down_sample3_3_2[row / 4 * col / 4];
    static double down_sample_filter3_1_2[row / 4 * col / 4], down_sample_filter3_2_2[row / 4 * col / 4], down_sample_filter3_3_2[row / 4 * col / 4];
    static double lp1_1_2[row*col], lp1_2_2[row*col], lp1_3_2[row*col];
    static double lp2_1_2[(row / 2)*(col / 2)], lp2_2_2[(row / 2)*(col / 2)], lp2_3_2[(row / 2)*(col / 2)];
    static double lp3_1_2[(row / 4)*(col / 4)], lp3_2_2[(row / 4)*(col / 4)], lp3_3_2[(row / 4)*(col / 4)];
    static double add3_1[row / 4 * col / 4], add3_2[row / 4 * col / 4], add3_3[row / 4 * col / 4];
    static double add2_1[row / 2 * col / 2], add2_2[row / 2 * col / 2], add2_3[row / 2 * col / 2];
    static double add1_1[row*col], add1_2[row*col], add1_3[row*col];
    static double Gadd3_1[row / 8 * col / 8], Gadd3_2[row / 8 * col / 8], Gadd3_3[row / 8 * col / 8];
    static double fusion_down_sample3_1[row / 4 * col / 4], fusion_down_sample3_2[row / 4 * col /4], fusion_down_sample3_3[row/4*col/4];
    static double fusion_filter3_1[row / 4 * col / 4], fusion_filter3_2[row / 4 * col / 4], fusion_filter3_3[row / 4 * col / 4];
    static double fusion3_1[row / 4 * col / 4], fusion3_2[row / 4 * col / 4], fusion3_3[row/4*col/4];
    static double fusion_down_sample2_1[row / 2 * col / 2], fusion_down_sample2_2[row / 2 * col / 2], fusion_down_sample2_3[row / 2 * col / 2];
    static double fusion_filter2_1[row / 2 * col / 2], fusion_filter2_2[row / 2 * col / 2], fusion_filter2_3[row / 2 * col / 2];
    static double fusion2_1[row / 2 * col / 2], fusion2_2[row / 2 * col / 2], fusion2_3[row/2*col/2];
    static double fusion_down_sample1_1[row * col], fusion_down_sample1_2[row * col], fusion_down_sample1_3[row * col];
    static double fusion_filter1_1[row* col], fusion_filter1_2[row* col], fusion_filter1_3[row* col];
    static double fusion1_1[row * col], fusion1_2[row * col], fusion1_3[row * col];
    static double add1[row*col], add2[row*col], add3[row*col];
    static double d_add1[row*col], d_add2[row*col], d_add3[row*col];
    int rowNumber2 = img2.rows;
    int colNumber2 = img2.cols * 3;

    for (int i = 0; i < img2.rows; i++)
    {
        uchar* data2 = img2.ptr<uchar>(i);
        for (int j = 0; j < colNumber2; j++)
        {
            if (j % 3 == 0) B2[i * col + (int)(j / 3)] = data2[j];
            if (j % 3 == 1) G2[i * col + (int)(j / 3)] = data2[j];
            if (j % 3 == 2) R2[i * col + (int)(j / 3)] = data2[j];
        }
    }
    //first layer of Guassin pyramid
    Gaussin_filter_up(B2, BF2, row, col, b2);
    Gaussin_filter_up(G2, GF2, row, col, b2);
    Gaussin_filter_up(R2, RF2, row, col, b2);
    up_sample_even(BF2, up_sample1_1_2, row, col);
    up_sample_even(GF2, up_sample1_2_2, row, col);
    up_sample_even(RF2, up_sample1_3_2, row, col);
    //Second layer of Guassin pyramid
    Gaussin_filter_up(up_sample1_1_2, BF2, row / 2, col / 2, b2);
    Gaussin_filter_up(up_sample1_2_2, GF2, row / 2, col / 2, b2);
    Gaussin_filter_up(up_sample1_3_2, RF2, row / 2, col / 2, b2);
    up_sample_even(BF2, up_sample2_1_2, row / 2, col / 2);
    up_sample_even(GF2, up_sample2_2_2, row / 2, col / 2);
    up_sample_even(RF2, up_sample2_3_2, row / 2, col / 2);
    //Third layer of Guassin pyrmaid
    Gaussin_filter_up(up_sample2_1_2, BF2, row / 4, col / 4, b2);
    Gaussin_filter_up(up_sample2_2_2, GF2, row / 4, col / 4, b2);
    Gaussin_filter_up(up_sample2_3_2, RF2, row / 4, col / 4, b2);
    up_sample_even(BF2, up_sample3_1_2, row / 4, col / 4);
    up_sample_even(GF2, up_sample3_2_2, row / 4, col / 4);
    up_sample_even(RF2, up_sample3_3_2, row / 4, col / 4);
    //O layer of Laplace pyramid
    down_sample(down_sample1_1_2, up_sample1_1_2, row, col, row / 2, col / 2);
    down_sample(down_sample1_2_2, up_sample1_2_2, row, col, row / 2, col / 2);
    down_sample(down_sample1_3_2, up_sample1_3_2, row, col, row / 2, col / 2);
    Gaussin_filter_down(down_sample1_1_2, down_sample_filter1_1_2, row, col, b2);
    Gaussin_filter_down(down_sample1_2_2, down_sample_filter1_2_2, row, col, b2);
    Gaussin_filter_down(down_sample1_3_2, down_sample_filter1_3_2, row, col, b2);
    lp_pyrmid(B2, down_sample_filter1_1_2, row, col,lp1_1_2);
    lp_pyrmid(G2, down_sample_filter1_2_2, row, col, lp1_2_2);
    lp_pyrmid(R2, down_sample_filter1_3_2, row, col, lp1_3_2);
    //First layer of Lapalce pyramid
    down_sample(down_sample2_1_2, up_sample2_1_2, row / 2, col / 2, row / 4, col / 4);
    down_sample(down_sample2_2_2, up_sample2_2_2, row / 2, col / 2, row / 4, col / 4);
    down_sample(down_sample2_3_2, up_sample2_3_2, row / 2, col / 2, row / 4, col / 4);
    Gaussin_filter_down(down_sample2_1_2, down_sample_filter2_1_2, row / 2, col / 2, b2);
    Gaussin_filter_down(down_sample2_2_2, down_sample_filter2_2_2, row / 2, col / 2, b2);
    Gaussin_filter_down(down_sample2_3_2, down_sample_filter2_3_2, row / 2, col / 2, b2);
    lp_pyrmid(up_sample1_1_2, down_sample_filter2_1_2, row / 2, col / 2, lp2_1_2);
    lp_pyrmid(up_sample1_2_2, down_sample_filter2_2_2, row / 2, col / 2, lp2_2_2);
    lp_pyrmid(up_sample1_3_2, down_sample_filter2_3_2, row / 2, col / 2, lp2_3_2);
    //Second layer of Laplace pyramid
    down_sample(down_sample3_1_2, up_sample3_1_2, row / 4, col / 4, row / 8, col / 8);
    down_sample(down_sample3_2_2, up_sample3_2_2, row / 4, col / 4, row / 8, col / 8);
    down_sample(down_sample3_3_2, up_sample3_3_2, row / 4, col / 4, row / 8, col / 8);
    Gaussin_filter_down(down_sample3_1_2, down_sample_filter3_1_2, row / 4, col / 4, b2);
    Gaussin_filter_down(down_sample3_2_2, down_sample_filter3_2_2, row / 4, col / 4, b2);
    Gaussin_filter_down(down_sample3_3_2, down_sample_filter3_3_2, row / 4, col / 4, b2);
    lp_pyrmid(up_sample2_1_2, down_sample_filter3_1_2, row / 4, col / 4, lp3_1_2);
    lp_pyrmid(up_sample2_2_2, down_sample_filter3_2_2, row / 4, col / 4, lp3_2_2);
    lp_pyrmid(up_sample2_3_2, down_sample_filter3_3_2, row / 4, col / 4, lp3_3_2);
    
    //Add laplace pyramid from two images
    AddWeighted(lp3_1, 0.5, lp3_1_2, 0.5, 0, add3_1, row / 4, col / 4);
    AddWeighted(lp3_2, 0.5, lp3_2_2, 0.5, 0, add3_2, row / 4, col / 4);
    AddWeighted(lp3_3, 0.5, lp3_3_2, 0.5, 0, add3_3, row / 4, col / 4);
    AddWeighted(lp2_1, 0.5, lp2_1_2, 0.5, 0, add2_1, row / 2, col / 2);
    AddWeighted(lp2_2, 0.5, lp2_2_2, 0.5, 0, add2_2, row / 2, col / 2);
    AddWeighted(lp2_3, 0.5, lp2_3_2, 0.5, 0, add2_3, row / 2, col / 2);
    AddWeighted(lp1_1, 0.5, lp1_1_2, 0.5, 0, add1_1, row, col);
    AddWeighted(lp1_2, 0.5, lp1_2_2, 0.5, 0, add1_2, row, col);
    AddWeighted(lp1_3, 0.5, lp1_3_2, 0.5, 0, add1_3, row, col);
   
    //Add Guassin pyrmid from two images
    AddWeighted(up_sample3_1, 0.5, up_sample3_1_2, 0.5, 0, Gadd3_1, row/8, col/8);
    AddWeighted(up_sample3_2, 0.5, up_sample3_2_2, 0.5, 0, Gadd3_2, row/8, col/8);
    AddWeighted(up_sample3_3, 0.5, up_sample3_3_2, 0.5, 0, Gadd3_3, row/8, col/8);
    
    //Guassin--> up sampling, add 0 in even rows and cols ====> the size of image is equal to the second layer of laplace pyramid
    down_sample(fusion_down_sample3_1, Gadd3_1, row / 4, col / 4, row / 8, col / 8);
    down_sample(fusion_down_sample3_2, Gadd3_2, row / 4, col / 4, row / 8, col / 8);
    down_sample(fusion_down_sample3_3, Gadd3_3, row / 4, col / 4, row / 8, col / 8);
    //void Gaussin_filter_down(int *down_sample, double* c_down, int down_row, int down_col, double *b_down)
    Gaussin_filter_down(fusion_down_sample3_1, fusion_filter3_1, row / 4, col / 4, b2);
    Gaussin_filter_down(fusion_down_sample3_2, fusion_filter3_2, row / 4, col / 4, b2);
    Gaussin_filter_down(fusion_down_sample3_3, fusion_filter3_3, row / 4, col / 4, b2);
    Add(fusion_filter3_1,add3_1,fusion3_1, row / 4, col / 4);
    Add(fusion_filter3_2, add3_2, fusion3_2, row / 4, col / 4);
    Add(fusion_filter3_3, add3_3, fusion3_3, row / 4, col / 4);
    down_sample(fusion_down_sample2_1, fusion3_1, row / 2, col / 2, row / 4, col / 4);
    down_sample(fusion_down_sample2_2, fusion3_2, row / 2, col / 2, row / 4, col / 4);
    down_sample(fusion_down_sample2_3, fusion3_3, row / 2, col / 2, row / 4, col / 4);
    Gaussin_filter_down(fusion_down_sample2_1, fusion_filter2_1, row / 2, col / 2, b2);
    Gaussin_filter_down(fusion_down_sample2_2, fusion_filter2_2, row / 2, col / 2, b2);
    Gaussin_filter_down(fusion_down_sample2_3, fusion_filter2_3, row / 2, col / 2, b2);
    Add(fusion_filter2_1, add2_1, fusion2_1, row / 2, col / 2);
    Add(fusion_filter2_2, add2_2, fusion2_2, row / 2, col / 2);
    Add(fusion_filter2_3, add2_3, fusion2_3, row / 2, col / 2);
    down_sample(fusion_down_sample1_1, fusion2_1, row , col, row / 2, col / 2);
    down_sample(fusion_down_sample1_2, fusion2_2, row , col , row / 2, col / 2);
    down_sample(fusion_down_sample1_3, fusion2_3, row, col, row / 2, col / 2);
    Gaussin_filter_down(fusion_down_sample1_1, fusion_filter1_1, row, col , b2);
    Gaussin_filter_down(fusion_down_sample1_2, fusion_filter1_2, row, col , b2);
    Gaussin_filter_down(fusion_down_sample1_3, fusion_filter1_3, row, col, b2);
    Add(fusion_filter1_1, add1_1, fusion1_1, row, col);
    Add(fusion_filter1_2, add1_2, fusion1_2, row, col);
    Add(fusion_filter1_3, add1_3, fusion1_3, row, col);
    AddWeighted(B, 0.5, B2, 0.5, 0, d_add1, row, col);
    AddWeighted(G, 0.5, G2, 0.5, 0, d_add2, row, col);
    AddWeighted(R, 0.5, R2, 0.5, 0, d_add3, row, col);

    for (int c2 = 0; c2 < (row)*(col); c2++)
    {
        data_out2[3 * c2 + 0] = (uchar)fusion1_1[c2];
        data_out2[3 * c2 + 1] = (uchar)fusion1_2[c2];
        data_out2[3 * c2 + 2] = (uchar)fusion1_3[c2];
    }

    Mat src1 = Mat(row, col, CV_8UC3, data_out2);
    namedWindow("green", WINDOW_AUTOSIZE);
    imshow("green", src1);
    //namedWindow("real", WINDOW_AUTOSIZE);
    //imshow("real", src2);
    //imwrite("Gfilter3_1.jpg", src1);
    //pyrDown
    waitKey(0);
    system("pause");
    return 0;
}

