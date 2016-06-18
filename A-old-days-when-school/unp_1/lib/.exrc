if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <Plug>(neocomplcache_start_omni_complete) 
inoremap <silent> <Plug>(neocomplcache_start_auto_complete_no_select) 
inoremap <silent> <Plug>(neocomplcache_start_auto_complete) =neocomplcache#mappings#popup_post()
inoremap <silent> <expr> <Plug>(neocomplcache_start_unite_quick_match) unite#sources#neocomplcache#start_quick_match()
inoremap <silent> <expr> <Plug>(neocomplcache_start_unite_complete) unite#sources#neocomplcache#start_complete()
imap <silent> <expr> <F5> (pumvisible() ? "\<Plug>LookupFileCE" : "")."\\<Plug>LookupFile"
inoremap <Plug>LookupFileCE 
inoremap <silent> <Plug>NERDCommenterInInsert  <BS>:call NERDComment(0, "insert")
inoremap <expr> <BS> neocomplcache#smart_close_popup()."\"
imap <F3> :NERDTreeToggle
smap <silent>  <Plug>(neocomplcache_snippets_expand)
nnoremap  h
nnoremap <NL> j
nnoremap  k
nnoremap  l
nmap  :BottomExplorerWindow
nmap  :FirstExplorerWindow
nnoremap <silent> w :CCTreeWindowToggle
nnoremap <silent> y :CCTreeWindowSaveCopy
nnoremap   @=((foldclosed(line('.')) < 0) ? 'zc' : 'zo')
nnoremap ' "
nmap <silent> ,n <Plug>MarkClear
vmap <silent> ,r <Plug>MarkRegex
nmap <silent> ,r <Plug>MarkRegex
vmap <silent> ,m <Plug>MarkSet
nmap <silent> ,m <Plug>MarkSet
nmap ,caL <Plug>CalendarH
nmap ,cal <Plug>CalendarV
nmap ,ihn :IHN
nmap ,is :IHS:A
nmap ,ih :IHS
nmap ,ca <Plug>NERDCommenterAltDelims
vmap ,cA <Plug>NERDCommenterAppend
nmap ,cA <Plug>NERDCommenterAppend
vmap ,c$ <Plug>NERDCommenterToEOL
nmap ,c$ <Plug>NERDCommenterToEOL
vmap ,cu <Plug>NERDCommenterUncomment
nmap ,cu <Plug>NERDCommenterUncomment
vmap ,cn <Plug>NERDCommenterNest
nmap ,cn <Plug>NERDCommenterNest
vmap ,cb <Plug>NERDCommenterAlignBoth
nmap ,cb <Plug>NERDCommenterAlignBoth
vmap ,cl <Plug>NERDCommenterAlignLeft
nmap ,cl <Plug>NERDCommenterAlignLeft
vmap ,cy <Plug>NERDCommenterYank
nmap ,cy <Plug>NERDCommenterYank
vmap ,ci <Plug>NERDCommenterInvert
nmap ,ci <Plug>NERDCommenterInvert
vmap ,cs <Plug>NERDCommenterSexy
nmap ,cs <Plug>NERDCommenterSexy
vmap ,cm <Plug>NERDCommenterMinimal
nmap ,cm <Plug>NERDCommenterMinimal
vmap ,c  <Plug>NERDCommenterToggle
nmap ,c  <Plug>NERDCommenterToggle
vmap ,cc <Plug>NERDCommenterComment
nmap ,cc <Plug>NERDCommenterComment
nmap <silent> ,lw :LUWalk
nmap <silent> ,ll :LUBufs
nmap <silent> ,lk :LUTags
map ,dc a /*  */<Left><Left><Left>
map ,db :DoxBlock
map ,df :Dox
map ,da :DoxAuthor
nmap <silent> ,wn :WMClose
nmap <silent> ,wm :WMToggle
map <silent> ,ee :call SwitchToBuf("~/.vimrc")
map <silent> ,ss :source ~/.vimrc
nnoremap ,' '
nmap <silent> ,lv :lv /=expand("<cword>")/ %:lw
nmap <silent> , :noh
map ,tm :tabmove
map ,tc :tabclose
map ,te :tabedit
map ,td :tabnew
map ,tp :tabprevious
map ,tn :tabnext
vmap [% [%m'gv``
vmap ]% ]%m'gv``
vmap a% [%v]%
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
nmap <silent> <F5> <Plug>LookupFile
nnoremap <silent> <Plug>CalendarH :cal Calendar(1)
nnoremap <silent> <Plug>CalendarV :cal Calendar(0)
nmap <silent> <Plug>NERDCommenterAppend :call NERDComment(0, "append")
nnoremap <silent> <Plug>NERDCommenterToEOL :call NERDComment(0, "toEOL")
vnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment(1, "uncomment")
nnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment(0, "uncomment")
vnoremap <silent> <Plug>NERDCommenterNest :call NERDComment(1, "nested")
nnoremap <silent> <Plug>NERDCommenterNest :call NERDComment(0, "nested")
vnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment(1, "alignBoth")
nnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment(0, "alignBoth")
vnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment(1, "alignLeft")
nnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment(0, "alignLeft")
vmap <silent> <Plug>NERDCommenterYank :call NERDComment(1, "yank")
nmap <silent> <Plug>NERDCommenterYank :call NERDComment(0, "yank")
vnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment(1, "invert")
nnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment(0, "invert")
vnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment(1, "sexy")
nnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment(0, "sexy")
vnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment(1, "minimal")
nnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment(0, "minimal")
vnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment(1, "toggle")
nnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment(0, "toggle")
vnoremap <silent> <Plug>NERDCommenterComment :call NERDComment(1, "norm")
nnoremap <silent> <Plug>NERDCommenterComment :call NERDComment(0, "norm")
nmap <C-/>d :cs find d =expand("<cword>")
nmap <C-/>i :cs find i ^=expand("<cfile>")$
nmap <C-/>f :cs find f =expand("<cfile>")
nmap <C-/>e :cs find e =expand("<cword>")
nmap <C-/>t :cs find t =expand("<cword>")
nmap <C-/>c :cs find c =expand("<cword>")
nmap <C-/>g :cs find g =expand("<cword>")
nmap <C-/>s :cs find s =expand("<cword>")
map <F3> :NERDTreeToggle
nnoremap <silent> <F4> :TlistToggle
map <F2> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .
map <Left> :bp
map <Right> :bn
nnoremap <C-S-CR> :bprevious
inoremap <expr>  neocomplcache#cancel_popup()
inoremap <expr>  neocomplcache#undo_completion()
inoremap <expr>  neocomplcache#smart_close_popup()."\"
inoremap <expr> 	 pumvisible() ? "\" : "\	"
inoremap <expr>  neocomplcache#complete_common_string()
inoremap <expr>  omni#cpp#maycomplete#Complete()
inoremap <expr>  neocomplcache#close_popup()
imap ,ihn :IHN
imap ,is :IHS:A
imap ,ih :IHS
inoremap , , 
inoremap <expr> . omni#cpp#maycomplete#Dot()
inoremap <expr> : omni#cpp#maycomplete#Scope()
inoremap <expr> > omni#cpp#maycomplete#Arrow()
let &cpo=s:cpo_save
unlet s:cpo_save
set ambiwidth=double
set autochdir
set autoread
set autowrite
set backspace=indent,eol,start
set backupcopy=yes
set completefunc=neocomplcache#complete#manual_complete
set completeopt=menuone,preview
set cscopeprg=/usr/bin/cscope
set cscopetag
set cscopetagorder=1
set cscopeverbose
set diffopt=filler,vertical
set fileencodings=UTF-8,gbk
set foldclose=all
set foldopen=block,hor,mark,percent,quickfix,tag
set formatoptions=tcqmM
set guicursor=n-v-c:block,o:hor50,i-ci:hor15,r-cr:hor30,sm:block,a:blinkon0
set helplang=cn
set hidden
set history=1000
set hlsearch
set ignorecase
set incsearch
set laststatus=2
set matchtime=2
set omnifunc=omni#cpp#complete#Main
set pastetoggle=<F3>
set report=0
set ruler
set scrolloff=10
set shiftwidth=4
set showmatch
set smartcase
set smartindent
set softtabstop=4
set statusline=\ %<%F[%1*%M%*%n%R%H]%=\ %y\ %0(%{&fileformat}\ %{&encoding}\ %c:%l/%L%)\\
set switchbuf=useopen
set tabstop=4
set tags=./tags,./TAGS,tags,TAGS,/usr/share/vim/vim73/doc/tags,$VIMFILES/doc/tags,~/.vim/tags/systags,~/.vim/tags/cpptags,../tags
set termencoding=utf-8
set whichwrap=b,s,<,>
set wildmenu
set nowrapscan
" vim: set ft=vim :
