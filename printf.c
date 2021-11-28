#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int count_chars;

static void	ft_putnbr(long nbr, int base_len, char *base)
{
	if (nbr >= base_len)
		ft_putnbr(nbr / base_len, base_len, base);
	write(1, &base[nbr % base_len], 1);
	count_chars++;
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	int i;
	int slen;
	int d;
	unsigned int x;
	char *str;

	va_start(ap, fmt);
	i = 0;	
	count_chars = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			while (fmt[i] == ' ' || fmt[i] == '\t')
				i++;
			if (fmt[i] == 'd')
			{
				d = va_arg(ap, int);
				if (d < 0)
				{
					unsigned int d1;
					d1 = -d;
					count_chars += write(1, "-", 1);
					ft_putnbr(d1, 10, "0123456789");
				}
				else
					ft_putnbr(d, 10, "0123456789");
			}
			else if (fmt[i] == 'x')
			{
				x = va_arg(ap, unsigned int);
				ft_putnbr(x, 16, "0123456789abcdef");
			}
			else if (fmt[i] == 's')
			{
				slen = 0;
				str = va_arg(ap, char *);
				if (str != NULL)
				{
					while (str[slen])
						slen++;
					count_chars += write(1, str, slen);
				}
				else
					count_chars += write(1, "(null)", 6);
			}
			else if (fmt[i])
				count_chars += write(1, &fmt[i], 1);
		}
		else if (fmt[i])
			count_chars += write(1, &fmt[i], 1);
		if (fmt[i])
			i++;
	}
	va_end(ap);
	return count_chars;
}

int main(void)
{
	int ret1, ret2;

	printf("%d\n", -2147483649);	
	ft_printf("%d\n", -2147483649);
	return 0;
}
