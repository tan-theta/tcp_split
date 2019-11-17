#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void tcp_split(char *input, char *output, char *ip, char *non_tcp)
{
char buf[BUFSIZ];
if (ip == NULL)
{
 	snprintf(buf, sizeof(buf), "\
#!/bin/sh \n\
num1=$(tshark -q -z conv,tcp -r %s | wc -l) \n\
num2=7 \n\
i=0 \n\
num3=$(expr $num1 - $num2) \n\
echo \"Number of TCP connections : $(expr $num1 - 6)\"\n\
mkdir -p %s\n\
while [ \"$i\" -le $num3 ]; do \n\
	tshark -nr %s -Y \"tcp.stream eq $i\" -w %s/$i.pcap \n\
	i=$(( i + 1 )) \n\
done\n\
", input, output, input, output);

int err = system(buf);
if (err) { fprintf(stderr, "failed to %s\n", buf); 
	exit(EXIT_FAILURE); }

}
	

if (ip != NULL)
{
 	snprintf(buf, sizeof(buf), "\
#!/bin/sh \n\
num1=$(tshark -q -z conv,tcp -r %s | wc -l) \n\
num2=7 \n\
i=0 \n\
num3=$(expr $num1 - $num2) \n\
echo \"Number of TCP connections : $(expr $num1 - 6)\"\n\
mkdir -p %s\n\
while [ \"$i\" -le $num3 ]; do \n\
	tshark -nr %s -Y \"tcp.stream eq $i and ip.dst!=%s and ip.src!=%s\" -w %s/$i.pcap \n\
	i=$(( i + 1 )) \n\
done\n\
", input, output, input,ip, ip, output);

int err = system(buf);
if (err) { fprintf(stderr, "failed to %s\n", buf); 
	exit(EXIT_FAILURE); }
}
 	

if (non_tcp != NULL){
        snprintf(buf, sizeof(buf), "\
#!/bin/sh \n\
tshark -nr %s -Y \"not tcp\" -w %s \n\
",input, non_tcp);
int err = system(buf);
if (err) { fprintf(stderr, "failed to %s\n", buf); 
	exit(EXIT_FAILURE); }
}
 	
}

int main (int argc, char **argv)
{
  char *input = NULL;
  char *output = NULL;
  char *src_ip = NULL;
  char *non_tcp = NULL;
  int index;
  int c;

  opterr = 0;


  while ((c = getopt (argc, argv, "i:o:f:j:")) != -1)
    switch (c)
      {
      case 'i':
        input = optarg;
        break;
      case 'o':
        output = optarg;
        break;
      case 'f':
        src_ip = optarg;
        break;
      case 'j':
        non_tcp = optarg;
        break;
      case '?':
        if (optopt == 'i')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (optopt == 'o')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (optopt == 'f')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (optopt == 'j')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }

  if (input == NULL) {
    printf("ERROR: Missing argument -i. No input file provided\n");
    exit(1);
  }

  if (output == NULL) {
    printf("ERROR: Missing argument -o. No output directory provided\n");
    exit(1);
  }

  tcp_split(input, output, src_ip, non_tcp);

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  return 0;
}
