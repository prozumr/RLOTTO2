#!/usr/bin/python
import argparse

parser = argparse.ArgumentParser(description='Create PDF manual from source code')
parser.add_argument('--header',     help='*.h files', required=True)
parser.add_argument('--csource',     help='*.c files', required=True)

args = parser.parse_args()

LATEXTSTART="""\\documentclass[a4paper,10pt]{scrartcl}
\\KOMAoptions{DIV=12}
\\parindent=0pt
\\usepackage{minted}	

\\setminted[C]{linenos,fontsize=\\footnotesize,tabsize=4}
\\setminted[make]{linenos,fontsize=\\footnotesize,tabsize=4}
\\setminted[python]{linenos,fontsize=\\footnotesize,tabsize=4}

% the following is needed for syntax highlighting
\\usepackage{color,hyperref}

\\hypersetup{backref,hidelinks,
colorlinks=false}
\\definecolor{dkgreen}{rgb}{0,0.6,0}
\\definecolor{gray}{rgb}{0.5,0.5,0.5}
\\definecolor{mauve}{rgb}{0.58,0,0.82}
\\begin{document}
\\underline{\\Large{\\textbf{RLOTTO Code Manual}}}
\\bigskip
\\tableofcontents
"""

print(LATEXTSTART)

#output Makefile
print("\\newpage\\section{{Makefile}}")
print("\\inputminted{make}{{../Makefile}}\\newpage")

# output *.h
print("\\newpage\\section{Header files}")
for f in args.header.split(" "):
	if f: 
		t = f.replace("_","\\_")
		print("\\subsection*{\\texttt{" + t + "}}")
		print("\\addcontentsline{toc}{subsection}{\\texttt{" + t + "}}")
		print("\\inputminted{C}{../" + f + "}\\newpage")

# output *.c
print("\\section{C Sourcecode}")
for f in args.csource.split(" "):
	if f: 
		t = f.replace("_","\\_")
		print("\\subsection*{\\texttt{" + t + "}}")
		print("\\addcontentsline{toc}{subsection}{\\texttt{" + t + "}}")
		print("\\inputminted{C}{../" + f + "}\\newpage")


# example ticket
print("\\section{Examples}")
print("\\subsection*{Ticket Input}")
print("\\addcontentsline{toc}{subsection}{Ticket Input}")
print("\\inputminted{text}{{../1234567.tck}}\\newpage")

# exmaple results
print("\\subsection*{Output Result}")
print("\\addcontentsline{toc}{subsection}{Output Result}")
print("\\inputminted{text}{{../results/Lotto-Result-2017-11-12.txt}}\\newpage")

print("""\\end{document}""")




