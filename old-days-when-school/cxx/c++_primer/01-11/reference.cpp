int main (void)
{
	int		ival = 1024;
	int		&refVal = ival;
	int		&refVal2;
	int		&refVal3 = 1024;
	int		&refRefval = refVal;

	const int iival = 1024;
	const int &refiVal = ival;
}
