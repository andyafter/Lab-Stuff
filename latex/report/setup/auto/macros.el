(TeX-add-style-hook
 "macros"
 (lambda ()
   (TeX-add-symbols
    '("danishprojectinfo" 8)
    '("englishprojectinfo" 8)
    '("aautitlepage" 3)
    "theoremframecommand")
   (LaTeX-add-environments
    '("example" 1))
   (LaTeX-add-lengths
    "titlepageleftcolumnwidth"
    "titlepagerightcolumnwidth"))
 :latex)

