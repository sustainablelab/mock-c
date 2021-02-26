# In folder code
- `;m<Space>`
    - build default target
- `;t<Space>`
    - close quickfix window

# In folder tests
- `;mt<Space>`
    - build default target
    - open quickfix window on right-hand side
    - open test results on bottom of screen
- `;t<Space>`
    - close quickfix window
    - close test results
- `:cclose`
    - close quickfix window without closing test results

# From either folder
- `;mca`
    - run the `clean` recipe
- `;cs`
    - connect to cscope.out
- `;cu`
    - create/update files tags and cscope.out
- `:make lib-tags`
    - create/update file lib-tags
