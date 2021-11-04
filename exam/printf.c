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
			else
				count_chars += write(1, &fmt[i], 1);
		}
		else
			count_chars += write(1, &fmt[i], 1);
		i++;
	}
	va_end(ap);
	return count_chars;
}

int main(void)
{
	int ret1, ret2;
	
	ret1 = ft_printf("%%\n");
	ret2 = printf("%%\n");
	printf("%d\n%d\n", ret1, ret2);
	return 0;
}