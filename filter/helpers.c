#include "helpers.h"
#include <math.h>



int sepiaRed(RGBTRIPLE input);
int sepiaGreen(RGBTRIPLE input);
int sepiaBlue(RGBTRIPLE input);

int getSum(RGBTRIPLE arr[], int clr );
int getCount (RGBTRIPLE arr[]);
void copyArr(int height , int width ,  RGBTRIPLE original[height][width] , RGBTRIPLE copy[height][width]);
RGBTRIPLE getPixel(int row , int col , int height, int width,  RGBTRIPLE image[height][width] );
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    for(int i = 0; i < height ; i++)
    {

        for(int j = 0; j < width ; j++)
        {
            //Get avg of all colors then set all values to that color. Round to nearest tenth.
            RGBTRIPLE curr = image[i][j];
            avg = round( (curr.rgbtRed + curr.rgbtBlue + curr.rgbtGreen)/3 );

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red , blue , green;

    for(int i = 0 ; i < height ; i++)
    {
        for(int j = 0 ; j < width ; j++)
        {
            RGBTRIPLE curr = image[i][j];

            red = sepiaRed(curr);
            blue = sepiaBlue(curr);
            green  = sepiaGreen(curr);

            image[i][j].rgbtRed = red;
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;

        }
    }
    return;
}
int sepiaRed(RGBTRIPLE input)
{
    int red =   round((.393 * input.rgbtRed
    + .769 * input.rgbtGreen
    + .189 * input.rgbtBlue) );
    if (red > 255 ) return 255;
    else return red;
}
int sepiaGreen(RGBTRIPLE input)
{
    int green =  round((.349 * input.rgbtRed +
    .686 * input.rgbtGreen
    + .168 * input.rgbtBlue));
    if (green  > 255) return 255;
    else return green;
}
int sepiaBlue(RGBTRIPLE input)
{
    int blue =  round(( .272 * input.rgbtRed
    +.534 * input.rgbtGreen
    +.131 * input.rgbtBlue));
    if (blue > 255) return 255;
    else return blue;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int count = 0;
    for(int i = 0; i < height ; i++)
    {
        for(int j = width -1; j >= width/2; j--)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][count];
            image[i][count] = temp;
            count++;
        }
        count = 0;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE imgCopy[height][width];
    RGBTRIPLE hold[9];
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {

            hold[0] = getPixel(i , j ,height , width, image );//Current 0,0
            hold[1] = getPixel(i, j + 1,height , width, image );// 0,1
            hold[2] = getPixel(i+ 1 , j + 1,height , width, image );//1,1
            hold[3] = getPixel(i+ 1, j,height , width, image );//1, 0
            hold[4] = getPixel(i + 1, j - 1,height , width, image );//1, -1
            hold[5] = getPixel(i , j - 1, height , width,image );//0,-1
            hold[6] = getPixel(i - 1, j - 1, height , width,image );//-1, -1
            hold[7] = getPixel(i - 1, j , height , width,image);//-1, 0
            hold[8] = getPixel(i - 1 , j + 1,height , width, image );//-1,1


            int nums = getCount(hold);
            //1 = blue 2 = green 3 = red
            int blue = round(getSum(hold, 1)/nums);
            int green = round(getSum(hold, 2)/nums);
            int red = round(getSum(hold, 3)/nums);


            //Function
            imgCopy[i][j].rgbtRed = red;
            imgCopy[i][j].rgbtBlue = blue;
            imgCopy[i][j].rgbtGreen = green;



        }
    }

    copyArr(height , width , image , imgCopy);
    return;
}

int getSum(RGBTRIPLE arr[], int clr ){
    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        if (arr[i].rgbtRed == 1 && arr[i].rgbtBlue == 2 )
        {

        }//Do nothing;
        else if (clr == 1)//blue
        {
            sum += arr[i].rgbtBlue;
        }
        else if (clr == 2)//green
        {
            sum += arr[i].rgbtGreen;
        }
        else //red
            sum += arr[i].rgbtRed;

    }
    return sum;
}
void copyArr(int height , int width ,  RGBTRIPLE original[height][width] , RGBTRIPLE copy[height][width])
{
    for(int i = 0; i < height ; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            original[i][j] = copy[i][j];
        }
    }
}
int getCount (RGBTRIPLE arr[])
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if (!(arr[i].rgbtRed == 1 && arr[i].rgbtBlue == 2))//NULL
        {
         count++;
        }
    }
    return count;
}
RGBTRIPLE getPixel(int row , int col , int height , int width , RGBTRIPLE image[height][width] )
{
    if(row < 0 || col < 0 || col >= width || row >= height )
    {
        RGBTRIPLE na;
        na.rgbtRed = 1;
        na.rgbtBlue = 2;
        return na;
    }
    return image[row][col];
}

