CSS
===

### 盒子大小
height
width
min-height
min-width
max-height
max-width

### 盒子轮廓
outline
outline-color
outline-offset
outline-style
outline-width

### 内容溢出处理方式
overflow
overflow-x
overflow-y
overflow-warp 原名：word-wrap

box-shadow
box-sizing

### 背景
background
background-image: none;
background-position: 0% 0%;
background-size: auto auto;
background-repeat: repeat;
background-origin: padding-box;
background-clip: border-box;
background-attachment: scroll;
background-color: transparent;

### 边框
border
border-radius
border-color
border-style
border-width
border-image
border-image-outset
border-image-repeat
border-image-slice
border-image-source
border-image-width
border-block-start
border-block-start-color
border-block-start-style
border-block-start-width
border-block-end
border-block-end-color
border-block-end-style
border-block-end-width
border-inline-start
border-inline-start-color
border-inline-start-style
border-inline-start-width
border-inline-end
border-inline-end-color
border-inline-end-style
border-inline-end-width
border-top
border-top-color
border-top-style
border-top-width
border-bottom
border-bottom-color
border-bottom-style
border-bottom-width
border-left
border-left-color
border-left-style
border-left-width
border-right
border-right-color
border-right-style
border-right-width
border-top-left-radius
border-top-right-radius
border-bottom-left-radius
border-bottom-right-radius

以下两个控制table的边框
border-collapse 设置表格的边框是否被合并为一个单一的边框。
                separate	默认值。边框会被分开。不会忽略 border-spacing 和 empty-cells 属性。
                collapse	如果可能，边框会合并为一个单一的边框。会忽略 border-spacing 和 empty-cells 属性。
                inherit	    规定应该从父元素继承 border-collapse 属性的值。
border-spacing  设置相邻单元格的边框间的距离（仅用于“边框分离”模式separate）。
                border-spacing: length
                border-spacing: horizontal vertical
                border-spacing: inherit

### 外边距
margin
margin-top
margin-bottom
margin-left
margin-right
margin-block-start
margin-block-end
margin-inline-start
margin-inline-end

### 内边距
pad
padding
padding-top
padding-bottom
padding-left
padding-right
padding-block-start
padding-block-end
padding-inline-start
padding-inline-end

### 定位
top
bottom
left
right
z-index
position
float
clear


### 字体
font
font-size
font-size-adjust
font-kerning
font-synthesis
font-language-override
font-weight (property)
font-weight (descriptor)
font-stretch (property)
font-stretch (descriptor)
font-style (property)
font-style (descriptor)
font-family (property)
font-family (descriptor)
font-feature-settings (property)
font-feature-settings (descriptor)
font-feature-settings (descriptor)
font-variant (property)
font-variant (descriptor)
font-variant-alternates
font-variant-caps
font-variant-east-asian
font-variant-ligatures
font-variant-numeric
font-variant-position

line-height

### 文本
text-align start | end | left | right | center | justify | match-parent
text-align-last start | end | left | right | center | justify | match-parent
text-combine-upright 
text-decoration 装饰文本
text-decoration-style
text-decoration-color
text-decoration-line
text-emphasis 该属性常用于设定中文排版中文本的着重样式
text-emphasis-style
text-emphasis-color
text-emphasis-position
text-indent 属性规定文本块中首行文本的缩进。
text-orientation 设定文本方向
text-overflow 设定文本溢出处理方式
text-rendering
text-shadow 设定文本阴影
text-transform 为文本块转换大小写
text-underline-position

text-justify

whitespace
direction
letter-spacing
word-spacing
line-height
word-warp

transform
transform-box
<transform-function>
transform-origin
transform-style

transition
transition-delay
transition-duration
transition-property
transition-timing-function

translate()
translate3d()
translatex()
translatey()
translatez()

An at-rule is a CSS statement beginning with an at sign, '@' (U+0040 COMMERCIAL AT), followed by an identifier and includes everything up to the next semi-colon, ';' (U+003B SEMICOLON), or the next CSS block, whichever comes first.

There are several at-rules, designated by their identifiers, each with a different syntax:

@charset — Defines the character set used by the style sheet.
@import — Tells the CSS engine to include an external style sheet.
@namespace — Tells the CSS engine that all its content must be considered prefixed with an XML namespace.
Nested at-rules — A subset of nested statements, which can be used as a statement of a style sheet as well as inside of conditional group rules:
@media — A conditional group rule which will apply its content if the device meets the criteria of the condition defined using a media query.
@supports   — A conditional group rule which will apply its content if the browser meets the criteria of the given condition.
@document  — A conditional group rule which will apply its content if the document in which the style sheet is applied meets the criteria of the given condition. (deferred to Level 4 of CSS Spec)
@page — Describes the aspect of layout changes which will be applied when printing the document.
@font-face — Describes the aspect of an external font to be downloaded.
@keyframes  — Describes the aspect of intermediate steps in a CSS animation sequence.
@viewport  — Describes the aspects of the viewport for small screen devices. (currently at the Working Draft stage)
@counter-style — Defines specific counter styles that are not part of the predefined set of styles. (at the Candidate Recommendation stage, but only implemented in Gekko as of writing)
@font-feature-values (plus @swash, @ornaments, @annotation, @stylistic, @styleset and @character-variant)
— Define common names in font-variant-alternates for feature activated differently in OpenType. (at the Candidate Recommendation stage, but only implemented in Gekko as of writing)
Conditional Group RulesEDIT
Much like the values of properties, each at-rule has a different syntax. Nevertheless, several of them can be grouped into a special category named conditional group rules. These statements share a common syntax and each of them can include nested statements—either rulesets or nested at-rules. Furthermore, they all convey a common semantic meaning—they all link some type of condition, which at any time evaluates to either true or false. If the condition evaluates to true, then all of the statements within the group will be applied.

Conditional group rules are defined in CSS Conditionals Level 3 and are:

@media,
@supports,
@document. (deferred to Level 4 of CSS Spec)
Since each conditional group may also contain nested statements, there may be an unspecified amount of nesting.