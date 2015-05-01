Translations
============

The Sibcoin Core project has been designed to support multiple localisations. This makes adding new phrases, and completely new languages easily achievable. For managing all application translations, Sibcoin Core makes use of the Transifex online translation management tool.

### Helping to translate (using Transifex)
Transifex is setup to monitor the Github repo for updates, and when code containing new translations is found, Transifex will process any changes. It may take several hours after a pull-request has been merged, to appear in the Transifex web interface.

### sibcoin-qt.pro

See the [Transifex Sibcoin project](https://www.transifex.com/projects/p/sibcoin/) to assist in translations. You should also join the translation mailing list for announcements - see details below.

### Writing code with translations
We use automated scripts to help extract translations in both Qt, and non-Qt source files. It is rarely necessary to manually edit the files in `src/qt/locale/`. The translation source files must adhere to the following format:
`sibcoin_xx_YY.ts or sibcoin_xx.ts`

`src/qt/locale/sibcoin_en.ts` is treated in a special way. It is used as the source for all other translations. Whenever a string in the source code is changed, this file must be updated to reflect those changes. A custom script is used to extract strings from the non-Qt parts. This script makes use of `gettext`, so make sure that utility is installed (ie, `apt-get install gettext` on Ubuntu/Debian). Once this has been updated, `lupdate` (included in the Qt SDK) is used to update `sibcoin_en.ts`.

```xml
<qresource prefix="/translations">
    <file alias="en">locale/sibcoin_en.qm</file>
    ...
</qresource>
```

`contrib/sibcoin-qt.pro` takes care of generating `.qm` (binary compiled) files from `.ts` (source files) files. It’s mostly automated, and you shouldn’t need to worry about it.

**Example Qt translation**
```cpp
QToolBar *toolbar = addToolBar(tr("Tabs toolbar"));
```

    sibcoin_xx_YY.ts or sibcoin_xx.ts

#### sibcoin_en.ts (Source file)

`src/qt/locale/sibcoin_en.ts` is treated in a special way. It is used as the
source for all other translations. Whenever a string in the code is changed
this file must be updated to reflect those changes. A custom script is used
to extract strings from the non-Qt parts. This script makes use of `gettext`,
so make sure that utility is installed (ie, `apt-get install gettext` on
Ubuntu/Debian). Once this has been updated, lupdate (included in the Qt SDK)
is used to update sibcoin_en.ts. This process has been automated, from src/,
simply run:
    make translate


### Creating a Transifex account
Visit the [Transifex Signup](https://www.transifex.com/signup/) page to create an account. Take note of your username and password, as they will be required to configure the command-line tool.

1. Open sibcoin_en.ts in Qt Linguist (also included in the Qt SDK)
2. Search for `%n`, which will take you to the parts in the translation that use plurals
3. Look for empty `English Translation (Singular)` and `English Translation (Plural)` fields
4. Add the appropriate strings for the singular and plural form of the base string
5. Mark the item as done (via the green arrow symbol in the toolbar)
6. Repeat from step 2. until all singular and plural forms are in the source file
7. Save the source file

### Installing the Transifex client command-line tool
The client it used to fetch updated translations. If you are having problems, or need more details, see [http://docs.transifex.com/developer/client/setup](http://docs.transifex.com/developer/client/setup)

**For Linux and Mac**

`pip install transifex-client`

    git add src/qt/sibcoinstrings.cpp src/qt/locale/sibcoin_en.ts
    git commit

```ini
nano ~/.transifexrc

[https://www.transifex.com]
hostname = https://www.transifex.com
password = PASSWORD
token =
username = USERNAME
```

https://www.transifex.com/projects/p/sibcoin/

Please see [http://docs.transifex.com/developer/client/setup#windows](http://docs.transifex.com/developer/client/setup#windows) for details on installation.

The Transifex Sibcoin project config file is included as part of the repo. It can be found at `.tx/config`, however you shouldn’t need change anything.

### Synchronising translations
To assist in updating translations, we have created a script to help.

1. `python contrib/devtools/update-translations.py`
2. update `src/qt/sibcoin.qrc` manually or via
   `ls src/qt/locale/*ts|xargs -n1 basename|sed 's/\(sibcoin_\(.*\)\).ts/        <file alias="\2">locale\/\1.qm<\/file>/'`
3. update `src/Makefile.qt.include` manually or via
   `ls src/qt/locale/*ts|xargs -n1 basename|sed 's/\(sibcoin_\(.*\)\).ts/  qt\/locale\/\1.ts \\/'`
4. `git add` new translations from `src/qt/locale/`

**Do not directly download translations** one by one from the Transifex website, as we do a few post-processing steps before committing the translations.

### Handling Plurals (in source files)
When new plurals are added to the source file, it's important to do the following steps:

1. Open `sibcoin_en.ts` in Qt Linguist (included in the Qt SDK)
2. Search for `%n`, which will take you to the parts in the translation that use plurals
3. Look for empty `English Translation (Singular)` and `English Translation (Plural)` fields
4. Add the appropriate strings for the singular and plural form of the base string
5. Mark the item as done (via the green arrow symbol in the toolbar)
6. Repeat from step 2, until all singular and plural forms are in the source file
7. Save the source file

### Translating a new language
To create a new language template, you will need to edit the languages manifest file `src/qt/bitcoin.qrc` and add a new entry. Below is an example of the english language entry.

```xml
<qresource prefix="/translations">
    <file alias="en">locale/sibcoin_en.qm</file>
    ...
</qresource>
```

**Note:** that the language translation file **must end in `.qm`** (the compiled extension), and not `.ts`.

### Questions and general assistance
Check official forum at [https://dashtalk.org/forums/dash-worldwide-collaboration.88/](https://dashtalk.org/forums/dash-worldwide-collaboration.88/).
