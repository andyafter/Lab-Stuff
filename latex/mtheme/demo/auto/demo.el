(TeX-add-style-hook
 "demo"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("beamer" "10pt")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("ccicons" "scale=2")))
   (add-to-list 'LaTeX-verbatim-environments-local "semiverbatim")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "ik"
    "rl"
    "beamer"
    "beamer10"
    "appendixnumberbeamer"
    "booktabs"
    "ccicons"
    "pgfplots"
    "xspace"
    "tikz"
    "tikz-3dplot"
    "algorithm2e")
   (TeX-add-symbols
    "themename")
   (LaTeX-add-labels
    "fig:gesture")
   (LaTeX-add-bibliographies))
 :latex)

