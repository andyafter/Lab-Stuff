(TeX-add-style-hook
 "master"
 (lambda ()
   (TeX-run-style-hooks
    "setup/preamble"
    "setup/hyphenations"
    "setup/macros"
    "sections/frontpage"
    "sections/colophon"
    "sections/titlepages"
    "sections/preface"
    "sections/introduction"
    "sections/ch2name"
    "sections/results"
    "sections/conclusion"
    "sections/appAname")
   (LaTeX-add-labels
    "bib:mybiblio"))
 :latex)

