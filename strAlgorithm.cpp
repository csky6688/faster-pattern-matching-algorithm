/*
��������ظ��ַ����ıȽ��㷨
2014��
wayitech
*/

#include "StdAfx.h"
#include "BmAlgorithm.h"
#include <string.h>
#include <time.h>

void BadChar(const char *ppattern, int nLen, int nBadArray[])
{
    for (int i = 0; i < 256; i++)
    {
        nBadArray[i] = -1;
    }
    for (int i = 0; i < nLen; i++)
    {
        nBadArray[(unsigned char)ppattern[i]] = i;
    }
}

void BadChar2(const char *ppattern,int nLen, int nBadArray2[])
{
    for (int i = 0; i < nLen; i++)
    {
        nBadArray2[i] = -1;
    }
    for (int i = nLen-1; i >= 0 ; i--)
	{        
		int j = i-1;
		for( ; j >=0 ; j-- )
		{
			if( (unsigned char)ppattern[j] == (unsigned char)ppattern[i] )
			{
				nBadArray2[i] = i -j;
				break;
			}
		}
		//nBadArray2[i] = -1;
	}
}

void NBox(const char *ppattern, int nLen, int *pNBox)
{
    if (0 == nLen)
    {
        return;
    }
    pNBox[nLen-1] = 0;
    int l = nLen-1;
    int r = nLen-1;
    for (int i = nLen-2; i >= 0; i--)
    {
        if (i < l)
        {
            int n = 0;
            for ( ; i >= n && ppattern[i-n] == ppattern[nLen-1-n]; n++);
            if (n > 0)
            {
                r = i;
                l = i-n+1;
            }
            pNBox[i] = n;
        }
        else
        {
            if (pNBox[i+nLen-1-r] < i-l+1)
            {
                pNBox[i] = pNBox[i+nLen-1-r];
            }
            else
            {
                int n = 1;
                for (int s = l+nLen-1-i; l >= n && ppattern[l-n] == ppattern[s-n]; n++);
                pNBox[i] = -(l-n-i);
                l = l-n+1;
                r = i;
            }
        }
    }
}

/************************************************************************/
/* ������ظ��Ӵ�                                                     */
/************************************************************************/

char* lnorepstr(char*  s, int *pnPos)
{
    char A[26];
    int  i, j;
    int  maxi = 0, maxlen = 0;
    int  len = strlen(s);

//    for(i = 0; i < 26; i++)
//        A[i] = -1;

    memset(A, -1, 26);
    for (i = 0; i < len; i++)
    {
        A[s[i] - 'a'] = 1;
        for(j = i+1 ; j < len; j++)
        {
            if(A[s[j]-'a'] == -1) //���ַ�û�г���
            {
                A[s[j]-'a'] = 1;
                if(j - i> maxlen)
                {
                    maxlen = j - i;
                    maxi = i;
                }
            }
            else
                break;
        }
        memset(A, -1, 26);
    }
	*pnPos = maxi;
   // printf("longest no repeat string: %.*s\n", maxlen+1, &s[maxi]);//
	char strRet[128];
	strncpy(strRet, &s[maxi], maxlen+1);
	strRet[maxlen+1] = '\0';
	return &strRet[0];
}

//
//void ZBox(const char* pattern, unsigned int length, unsigned int zbox[])    
//{  
//    zbox[0] = 0;  
//    unsigned int left = 0;  
//    unsigned int right = 0;  
//    for (unsigned int i = 1; i < length; i++)  
//    {  
//        if (i > right)//���3   
//        {  
//            int n = 0;  
//            for ( ; pattern[n] == pattern[i+n]; n++);  
//            if (0 != n)  
//            {  
//                right = i+n-1;  
//                left = i;  
//            }  
//            zbox[i] = n;  
//        }  
//        else  
//        {  
//            if (zbox[i-left] < right-i+1)//���1   
//            {  
//                zbox[i] = zbox[i-left];  
//            }  
//            else//���2   
//            {  
//                int n = 1;  
//                for (;pattern[right-i+n] == pattern[right+n]; n++);  
//                zbox[i] = right-i+n;  
//                right += n-1;  
//                left = i;  
//            }  
//        }  
//        printf(" zbox[%d] = %d, left is %d, right is %d\r\n", i,  zbox[i], left, right);  
//    }  
//}  


bool GoodSuffix(const char *ppattern, int nLen, int nGoodArray[])
{
    if (0 == nLen)
    {
        return false;
    }
    //��ֱ����ú�׺���飬��Ϊֱ����Ļ�ʱ�临�Ӷ���O��n��ƽ����
    //�����ȼ����N-BOX����
    int *pNBox = new int[nLen];
    if (!pNBox)
    {
        return false;
    }

    NBox(ppattern, nLen, pNBox);
    
    //����N-BOXȷ���ú�׺��ֵ������ȫ����ʼ��Ϊ-1
    for (int i = 0; i < nLen; i++)
    {
        nGoodArray[i] = -1;
    }
    //��һ���������ȫƥ��L'(i)
    int nMax = 0;
    for (int i = 0; i < nLen; i++)
    {
        nGoodArray[nLen-1-pNBox[i]] = i;
        if (pNBox[i] == i+1)
        {
            nMax = i+1;
        }
    }
    nGoodArray[nLen-1] = -1;
    //�ڶ������������ƥ��l'(i) ǰ׺�ͺ�׺��ƥ��
    if (nMax != 0)
    {
        for (int i = 0; i < nLen-1-nMax; i++)
        {
            if (nGoodArray[i] == -1)
            {
                nGoodArray[i] = nMax-1;
            }
        }
    }
    nGoodArray[nLen-1] = nLen-2;
    if (pNBox)
    {
        delete pNBox;
        pNBox = NULL;
    }
    return true;
}

int BadCharSearch(const char* pDest, int nDLen, const char* ppattern, int nPLen, int *nBadArray)
{
    int nDstart = nPLen-1;
    while (nDstart < nDLen)
    {
        int i = 0;
        for (; i <= nPLen-1 && pDest[nDstart-i] == ppattern[nPLen-1-i]; i++);
        if (i > nPLen-1)
        {
            return nDstart - (nPLen-1);
        }
        int nIdx = nBadArray[pDest[nDstart-i]];
        if (nIdx >= nPLen-1-i)//if nIdx is greater than or equal to mismatch position, just move pattern[i] to right 1 character 
        {
            nDstart = nDstart + 1;
        }
        else
        {
            nDstart = nDstart + (nPLen-1-i - nIdx);
        }
    }
    return -1;
}

int GoodSuffixSearch(const char* pDest, int nDLen, const char* ppattern, int nPLen, int *nGoodArray)
{
    int nDstart = nPLen-1;
    while (nDstart < nDLen)
    {
        int i = 0;
        for (; i <= nPLen-1 && pDest[nDstart-i] == ppattern[nPLen-1-i]; i++);
        if (i > nPLen-1)
        {
            return nDstart - (nPLen-1);
        }
        int nIdx = nGoodArray[nPLen-1-i];
        nDstart = nDstart + (nPLen-1 - nIdx);
    }
    return -1;
}

//����ظ��ַ����㷨
int NewSearch(const char* pDest, int nDLen,
			  const char* ppattern, int nPLen,
			  const char* pStrmost, int nLenmost,
			  int nmostStart, int *nGoodArray, 
			  int *nBadArray, int *nBadArray2)
{
	//�㷨�����������Ƚϵ�
	//1.ĩλ�ַ��Ƚ�
	//2.����ظ��ַ�����ĩλ�Ƚ�

	if( 0 == nPLen )
	{
		return  -1;
	}

	int nDstart = nPLen - 1 ;
	int nStrPattern = nmostStart + nLenmost - 1;//��Ӵ�ĩλ�ַ�λ��
	int nEndmostLen = nPLen - nStrPattern -1 ;    //��Ӵ�ĩλ�ַ�����ģʽ��β����
	int lenMost = nLenmost+nmostStart;
	int i = 0;
	int j = 0;
	int nIdxBad = 0;
	int nShiftBad = 0;
	int nShiftBad2 = 0;		int sum = 0;


	if(1)
	{   //sunday�㷨
		while( nDstart < nDLen )
		{
			i = 0;
			sum++;
			//�ȽϹ����ַ���
			for(; i <= nPLen - 1 && pDest[nDstart-i] == ppattern[nPLen-i-1]; i++);	

			//nIdxBad    = nBadArray[pDest[nDstart]];
			if (i >= nPLen-1)
			{
				return nDstart - (nPLen-1);
			}
			else  //�ַ������ϣ�����sunday�㷨��ת
			{
				nIdxBad     = nBadArray[pDest[nDstart+1]];	
				nShiftBad   = nPLen - nIdxBad;

				//nDstart += (nShiftGood > nShiftBad) ? nShiftGood : nShiftBad;		
				nDstart += nShiftBad;
				continue;
			}
		}
	}
	else
	{

		while( nDstart < nDLen )
		{
			i =0; sum++;
			j = (pDest[nDstart] == ppattern[nPLen - 1])?1:0;
			nIdxBad    = nBadArray[pDest[nDstart]];
			if(nIdxBad == -1)
			{
				nDstart += nPLen;
				continue;
			}
			else if(j != 1)  //ĩλ�ַ������ϣ�����sunday�㷨��ת
			{
				nShiftBad2 = nPLen-1-nIdxBad;
				nIdxBad = 0;

				nIdxBad     = nBadArray[pDest[nDstart+1]];	
				nShiftBad   = nPLen - nIdxBad;

				//nDstart += (nShiftGood > nShiftBad) ? nShiftGood : nShiftBad;		
				nDstart += (nShiftBad > nShiftBad2)?nShiftBad:nShiftBad2;
				continue;
			}
			//�Ƚ�����ظ��ַ���
			for(; i <= nStrPattern - 1 && pDest[nDstart-nEndmostLen-i] == ppattern[nStrPattern-i]; i++);
			if( (i > nStrPattern - 1) )
			{//����ƥ��ɹ�,��ַ�����֮ǰƥ��ɹ�
				i = 0;
				for(; i < nEndmostLen &&  pDest[nDstart-i-1] == ppattern[nPLen-2-i];i++); //�Ƚ���ַ���֮���ģʽ�ִ�

				if(i == nEndmostLen)
				{			
					return nDstart-(nPLen-1);				
				} 
				else
				{
					nIdxBad     = nBadArray[pDest[nDstart+1]];	
					nShiftBad   = nPLen - nIdxBad;

					nDstart += nLenmost>nShiftBad?nLenmost:nShiftBad;  //��������ظ������Ⱥͻ��ַ������ֵ��ת
				}
			}
			else
			{
				nIdxBad = nBadArray2[pDest[nDstart-nEndmostLen-i]];
				nShiftBad2 = nStrPattern -nIdxBad ;  //����ظ��ַ������ַ���ת

				nIdxBad = 0;

				nIdxBad     = nBadArray[pDest[nDstart+1]];	
				nShiftBad   = nPLen - nIdxBad;

				//nDstart += (nShiftGood > nShiftBad) ? nShiftGood : nShiftBad;		
				nDstart += (nShiftBad > nShiftBad2)?nShiftBad:nShiftBad2;
			}
		}
	}
	return -1;
}

int BMSearch(const char* pDest, int nDLen, 
             const char* ppattern, int nPLen, 
             int *nGoodArray, int *nBadArray)
{
    if (0 == nPLen)
    {
        return -1;
    }
    int nDstart = nPLen-1;
	int sum =0 ;
    while (nDstart < nDLen)
    {
		sum++;
        int i = 0;
        for (; i <= nPLen-1 && pDest[nDstart-i] == ppattern[nPLen-1-i]; i++);
        if (i > nPLen-1)
        {
            return nDstart - (nPLen-1);
        }
        int nIdxGood    = nGoodArray[nPLen-1-i];
        int nShiftGood  = nPLen-1 - nIdxGood;

        int nIdxBad     = nBadArray[pDest[nDstart-i]];
        int nShiftBad   = (nIdxBad >= nPLen-1-i) ? 1 : nPLen-1-i - nIdxBad;

        nDstart += (nShiftGood > nShiftBad) ? nShiftGood : nShiftBad;
    }
    return -1;
}

void TestBMSearch()
{
    int         nFind;
    int         nGoodArray[100] = {0};
    int         nBadArray[256]  = {0};
	int         nBadArray2[256]  = {0};

                               //        1         2         3         4
                               //0123456789012345678901234567890123456789012345678901234
    const char  dest[]      =   "abcxxxbaaxueriwqjskdfcksejdfdj.,jsdfeskdfcksejxfvweofrdsjfw9erbbxeoirdslfjksdfkdsfkjskdfcksejskfejsdfksjfjksdfaabaaasdfsdfdsfsdfxbbaaabcdaajsdfeskdfcksejdfsdfdsfesdkeaaxbbxasdfdsfesdbxa.cxb";
    char  pattern[][20] = {
		"eskdfcksejdfsdfdsfe",
		"abcdaa",
		"abcda",
		"jfks",  
		"jsdfeskdfcksejdf",
        "abcda",
        "xxx",
        "ax",
        "xb",
        "bddd",
        "sdfdsfesdke",
        "aaabaaaab",
        "baaaabaaa",
    };



	{
		for (int i = 0; i < 1;i++)//sizeof(pattern)/sizeof(pattern[0]); i++)
		{
			BadChar(pattern[i], strlen(pattern[i]), nBadArray);
			GoodSuffix(pattern[i], strlen(pattern[i]), nGoodArray);

			//if (-1 != nFind)
			//{
			//    printf("Found    \"%s\" at %d \t%s\r\n", pattern[i], nFind, dest+nFind);
			//}
			//else
			//{
			//    printf("Found    \"%s\" no result.\r\n", pattern[i]);
			//}
			int nPos;
			char pCh[128];
			char pCh2[128];
			strcpy(pCh, lnorepstr(pattern[i], &nPos));
			strncpy(pCh2, pattern[i], strlen(pCh)+nPos);
			pCh2[strlen(pCh)+nPos] = '\0';
			BadChar(pCh2, strlen(pCh2), nBadArray2);
			int kTemp = 0;
			int tEnd = 0;
			double t = 0.00;

			int tStart;
			//	tStart = clock();

			//for(;kTemp < 56200;kTemp++)
			//{
			//	nFind = NewSearch(dest, strlen(dest),pattern[i], strlen(pattern[i]), pCh, strlen(pCh),nPos,nGoodArray, nBadArray, nBadArray2); 
			//}	

			// tEnd = clock();			
			// t = (double)(tEnd - tStart)/CLOCKS_PER_SEC;

			printf("%lf seconds is used\n", t);
			
			tStart = clock();
			for(;kTemp < 56200;kTemp++)
			{
			nFind = BMSearch(dest, strlen(dest), pattern[i], strlen(pattern[i]), nGoodArray, nBadArray);
			}
			tEnd = clock();

			t = (double)(tEnd - tStart)/CLOCKS_PER_SEC;
			printf("%lf seconds is used\n", t);

			if (-1 != nFind)
			{
				//printf("Found    \"%s\" at %d \t%s\r\n", pattern[i], nFind, dest+nFind);
			}   
		}	

	}		

}
int test();

//NewSearchΪ������ĸ�������ظ��ַ����ĸĽ�Sunday�㷨
//BmSearchΪBM�㷨 ��NewSearch����Sunday�㷨ʵ��

int _tmain(int argc, _TCHAR* argv[])
{
    TestBMSearch();
	//test();
	printf("Test Searchend\r\n");
    return 0;
}