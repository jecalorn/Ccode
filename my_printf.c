

extern void sensor_hub_printf(const char *format, ...);
extern void sensor_hub_print_buff(const char *buff_name,unsigned char *buf, int len, const char* func, int line);
#define LOG_BUFF(buf, len) sensor_hub_print_buff(#buf,buf,len,__func__,__LINE__)
#define LOGERROR(x,...)  if (log_level >= 0)   {sensor_hub_printf(x,##__VA_ARGS__);}
#define LOGWARN(x,...)   if (log_level >= 1)   {sensor_hub_printf(x,##__VA_ARGS__);}
#define LOGINFO(x,...)   if (log_level >= 2)   {sensor_hub_printf(x,##__VA_ARGS__);}
#define LOGDEBUG(x,...)  if (log_level >= 3)   {sensor_hub_printf(x,##__VA_ARGS__);}

#include <pwd.h>
void print_buff(const char *buff_name,unsigned char *buf, int len, const char* func, int line)
{
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/stat.h>  

//#define TEST_LOG_FILE "/home/log/sensorhub.log"
//#define TEST_LOG_PATH "/home/log/"

    va_list args;
    FILE *fp;
    int filelen = 0;
    bool to_file = false;
    char TEST_LOG_FILE[40];
    char TEST_LOG_PATH[40];

    time_t timet;
    struct tm *p;

    {
        struct passwd *pwd;
        pwd = getpwuid(getuid());
        //printf("current uid:  (%s)\n", pwd->pw_name);
        memset((unsigned char *)TEST_LOG_FILE, 0, sizeof(TEST_LOG_FILE));
        memset((unsigned char *)TEST_LOG_PATH, 0, sizeof(TEST_LOG_PATH));
        if(memcmp(pwd->pw_name,"root",4) == 0)
        {
            sprintf(TEST_LOG_PATH,"/home/log/",pwd->pw_name);        
            sprintf(TEST_LOG_FILE,"/home/log/sensorhub.log",pwd->pw_name);        
        }
        else
        {
            sprintf(TEST_LOG_PATH,"/home/%s/log/",pwd->pw_name);        
            sprintf(TEST_LOG_FILE,"/home/%s/log/sensorhub.log",pwd->pw_name);        
        }
    }

    if(access(TEST_LOG_PATH,F_OK) != 0)
    {
        if(mkdir(TEST_LOG_PATH, 0777 )!= 0)\
            to_file = true;
    }
    else
    {
        to_file = true;
    }

    //print to console
    {
        int i = 0;
        printf("----------------------------------------------------------\r\n");
        printf("LINE    : %d\r\n", line);
        printf("func    : %s\r\n", func);
        printf("name    : %s\r\n", buff_name);
        printf("len     : %d\r\n", len);
        printf("          00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\r\n");
        printf("----------------------------------------------------------\r\n");

        for(i = 0; i<len; i++)
        {
            if((i%16) == 0)
            {
                printf("%08x  ",(buf+i));
            }
        
            printf("%02x ",buf[i]&0xFF);

            if((i%16) == 7)
            {
                printf(" ");
            }

            if((i%16) == 15)
            {
                printf("\r\n");
            }
        }
        printf("\r\n----------------------------------------------------------\r\n");
    }
    
    if(to_file == false)
    {
        return;
    }

    {
        int i = 0;

        fp = fopen(TEST_LOG_FILE, "a+");
        if(fp == NULL) return;

        fseek(fp, 0, SEEK_END);
        time(&timet);
        p = localtime(&timet);

        fprintf(fp,"[%d_%02d_%02d %02d:%02d:%02d]\r\n", (p ->tm_year + 1900), p ->tm_mon, p ->tm_mday, p ->tm_hour, p ->tm_min, p ->tm_sec);
        fprintf(fp,"----------------------------------------------------------\r\n");
        fprintf(fp,"LINE    : %d\r\n", line);
        fprintf(fp,"func    : %s\r\n", func);
        fprintf(fp,"name    : %s\r\n", buff_name);
        fprintf(fp,"len     : %d\r\n", len);
        fprintf(fp,"          00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\r\n");
        fprintf(fp,"----------------------------------------------------------\r\n");

        for(i = 0; i<len; i++)
        {
            if((i%16) == 0)
            {
                fprintf(fp,"%08x  ",(buf+i));
            }
        
            fprintf(fp,"%02x ",buf[i]&0xFF);

            if((i%16) == 7)
            {
                fprintf(fp," ");
            }

            if((i%16) == 15)
            {
                fprintf(fp,"\r\n");
            }
        }
        fprintf(fp,"\r\n----------------------------------------------------------\r\n");

        fclose(fp);
    }

}

/*
----------------------------------------------------------
func    :
name    :
len     :
          00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F 
----------------------------------------------------------
00000000  00 01 02 03 00 01 02 03  00 01 02 03 00 01 02 03

----------------------------------------------------------
*/

void printf(const char *format, ...)
{
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/stat.h>  

#define TEST_LOG_FILE_MAX_LEN 50*1024*1024
//#define TEST_LOG_FILE "/home/log/sensorhub.log"
//#define TEST_LOG_PATH "/home/log/"

    va_list args;
    FILE *fp;
    int filelen = 0;
    bool to_file = false;
    char TEST_LOG_FILE[40];
    char TEST_LOG_PATH[40];

    time_t timet;
    struct tm *p;

    {
        struct passwd *pwd;
        pwd = getpwuid(getuid());
        //printf("current uid:  (%s)\n", pwd->pw_name);
        memset((unsigned char *)TEST_LOG_FILE, 0, sizeof(TEST_LOG_FILE));
        memset((unsigned char *)TEST_LOG_PATH, 0, sizeof(TEST_LOG_PATH));
        if(memcmp(pwd->pw_name,"root",4) == 0)
        {
            sprintf(TEST_LOG_PATH,"/home/log/",pwd->pw_name);        
            sprintf(TEST_LOG_FILE,"/home/log/sensorhub.log",pwd->pw_name);        
        }
        else
        {
            sprintf(TEST_LOG_PATH,"/home/%s/log/",pwd->pw_name);        
            sprintf(TEST_LOG_FILE,"/home/%s/log/sensorhub.log",pwd->pw_name);        
        }
    }

    if(access(TEST_LOG_PATH,F_OK) != 0)
    {
        if(mkdir(TEST_LOG_PATH, 0777 )!= 0)\
            to_file = true;
    }
    else
    {
        to_file = true;
    }

    //print to console
    {
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }

    if(to_file == false)
    {
        return;
    }

    fp = fopen(TEST_LOG_FILE, "a+");

    if(fp == NULL) return;
    
    fseek(fp, 0, SEEK_END);
    time(&timet);
    p = localtime(&timet);
    fprintf(fp,"[%d_%02d_%02d %02d:%02d:%02d]", (p ->tm_year + 1900), p ->tm_mon, p ->tm_mday, p ->tm_hour, p ->tm_min, p ->tm_sec);
    va_start(args, format);
    vfprintf(fp, format, args);
    va_end(args);
    filelen = ftell(fp);
    fclose(fp);

    if (filelen > TEST_LOG_FILE_MAX_LEN)
    {
        remove(TEST_LOG_FILE);
    }
}
