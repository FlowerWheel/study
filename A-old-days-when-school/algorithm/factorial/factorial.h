#ifndef FAC
#define FAC
void multi(char *multiplicand, char *multiplier)
{
	int		multiplicand_len;
	int		multiplier_len;
	int		i, j, begin;	
	int		carry_over;
	int		product;
	int		zero_count;

	multiplicand_len = strlen(multiplicand);
	multiplier_len = strlen(multiplier);

	for(i = M_LENTH - 1; i >= (begin = M_LENTH - multiplier_len); i--)
	{
		if(multiplier[i] != 0)
		{
			carry_over = 0;
			zero_count = i - begin; 
			for(j = M_LENTH - multiplicand_len; j <= M_LENTH - 1; j++)
			{
				product = (int)multiplier[i] * (int)multiplicand[j] + carry_over;
				carry_over = product / 10;
				multiplicand[j-1]	= (char)(product % 10);
			}
			multiplicand[j] = carry_over;
			if(carry_over)
				multiplicand_len++;
			multiplicand_len += zero_count;
		}
	}
}
#endif
