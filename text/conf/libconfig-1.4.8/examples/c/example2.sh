#! /bin/sh

# example2 - temporary wrapper script for .libs/example2
# Generated by ltmain.sh (GNU libtool) 2.2.6b
#
# The example2 program cannot be directly executed until all the libtool
# libraries that it depends on are installed.
#
# This wrapper script should never be moved out of the build directory.
# If it is, it will not operate correctly.

# Sed substitution that helps us do robust quoting.  It backslashifies
# metacharacters that are still active within double-quoted strings.
Xsed='/bin/sed -e 1s/^X//'
sed_quote_subst='s/\([`"$\\]\)/\\\1/g'

# Be Bourne compatible
if test -n "${ZSH_VERSION+set}" && (emulate sh) >/dev/null 2>&1; then
  emulate sh
  NULLCMD=:
  # Zsh 3.x and 4.x performs word splitting on ${1+"$@"}, which
  # is contrary to our usage.  Disable this feature.
  alias -g '${1+"$@"}'='"$@"'
  setopt NO_GLOB_SUBST
else
  case `(set -o) 2>/dev/null` in *posix*) set -o posix;; esac
fi
BIN_SH=xpg4; export BIN_SH # for Tru64
DUALCASE=1; export DUALCASE # for MKS sh

# The HP-UX ksh and POSIX shell print the target directory to stdout
# if CDPATH is set.
(unset CDPATH) >/dev/null 2>&1 && unset CDPATH

relink_command="(cd /root/workspace/exercise/c/text/conf/libconfig-1.4.8/examples/c; { test -z \"\${LIBRARY_PATH+set}\" || unset LIBRARY_PATH || { LIBRARY_PATH=; export LIBRARY_PATH; }; }; { test -z \"\${COMPILER_PATH+set}\" || unset COMPILER_PATH || { COMPILER_PATH=; export COMPILER_PATH; }; }; { test -z \"\${GCC_EXEC_PREFIX+set}\" || unset GCC_EXEC_PREFIX || { GCC_EXEC_PREFIX=; export GCC_EXEC_PREFIX; }; }; { test -z \"\${LD_RUN_PATH+set}\" || unset LD_RUN_PATH || { LD_RUN_PATH=; export LD_RUN_PATH; }; }; { test -z \"\${LD_LIBRARY_PATH+set}\" || unset LD_LIBRARY_PATH || { LD_LIBRARY_PATH=; export LD_LIBRARY_PATH; }; }; PATH=/usr/lib64/qt-3.3/bin:/usr/local/sbin:/usr/sbin:/sbin:/usr/local/bin:/usr/bin:/bin:/root/bin; export PATH; gcc -g -O2 -Wall -Wshadow -Wextra -Wdeclaration-after-statement -Wno-unused-parameter -o \$progdir/\$file example2.o  ../../lib/.libs/libconfig.so -Wl,-rpath -Wl,/root/workspace/exercise/c/text/conf/libconfig-1.4.8/lib/.libs -Wl,-rpath -Wl,/usr/local/lib)"

# This environment variable determines our operation mode.
if test "$libtool_install_magic" = "%%%MAGIC variable%%%"; then
  # install mode needs the following variables:
  generated_by_libtool_version='2.2.6b'
  notinst_deplibs=' ../../lib/libconfig.la'
else
  # When we are sourced in execute mode, $file and $ECHO are already set.
  if test "$libtool_execute_magic" != "%%%MAGIC variable%%%"; then
    ECHO="echo"
    file="$0"
    # Make sure echo works.
    if test "X$1" = X--no-reexec; then
      # Discard the --no-reexec flag, and continue.
      shift
    elif test "X`{ $ECHO '\t'; } 2>/dev/null`" = 'X\t'; then
      # Yippee, $ECHO works!
      :
    else
      # Restart under the correct shell, and then maybe $ECHO will work.
      exec /bin/sh "$0" --no-reexec ${1+"$@"}
    fi
  fi

  # Find the directory that this script lives in.
  thisdir=`$ECHO "X$file" | $Xsed -e 's%/[^/]*$%%'`
  test "x$thisdir" = "x$file" && thisdir=.

  # Follow symbolic links until we get to the real thisdir.
  file=`ls -ld "$file" | /bin/sed -n 's/.*-> //p'`
  while test -n "$file"; do
    destdir=`$ECHO "X$file" | $Xsed -e 's%/[^/]*$%%'`

    # If there was a directory component, then change thisdir.
    if test "x$destdir" != "x$file"; then
      case "$destdir" in
      [\\/]* | [A-Za-z]:[\\/]*) thisdir="$destdir" ;;
      *) thisdir="$thisdir/$destdir" ;;
      esac
    fi

    file=`$ECHO "X$file" | $Xsed -e 's%^.*/%%'`
    file=`ls -ld "$thisdir/$file" | /bin/sed -n 's/.*-> //p'`
  done


  # Usually 'no', except on cygwin/mingw when embedded into
  # the cwrapper.
  WRAPPER_SCRIPT_BELONGS_IN_OBJDIR=no
  if test "$WRAPPER_SCRIPT_BELONGS_IN_OBJDIR" = "yes"; then
    # special case for '.'
    if test "$thisdir" = "."; then
      thisdir=`pwd`
    fi
    # remove .libs from thisdir
    case "$thisdir" in
    *[\\/].libs ) thisdir=`$ECHO "X$thisdir" | $Xsed -e 's%[\\/][^\\/]*$%%'` ;;
    .libs )   thisdir=. ;;
    esac
  fi

  # Try to get the absolute directory name.
  absdir=`cd "$thisdir" && pwd`
  test -n "$absdir" && thisdir="$absdir"

  program=lt-'example2'
  progdir="$thisdir/.libs"

  if test ! -f "$progdir/$program" ||
     { file=`ls -1dt "$progdir/$program" "$progdir/../$program" 2>/dev/null | /bin/sed 1q`; \
       test "X$file" != "X$progdir/$program"; }; then

    file="$$-$program"

    if test ! -d "$progdir"; then
      mkdir "$progdir"
    else
      rm -f "$progdir/$file"
    fi

    # relink executable if necessary
    if test -n "$relink_command"; then
      if relink_command_output=`eval $relink_command 2>&1`; then :
      else
	echo "$relink_command_output" >&2
	rm -f "$progdir/$file"
	exit 1
      fi
    fi

    mv -f "$progdir/$file" "$progdir/$program" 2>/dev/null ||
    { rm -f "$progdir/$program";
      mv -f "$progdir/$file" "$progdir/$program"; }
    rm -f "$progdir/$file"
  fi

  if test -f "$progdir/$program"; then
    if test "$libtool_execute_magic" != "%%%MAGIC variable%%%"; then
      # Run the actual program with our arguments.

      exec "$progdir/$program" ${1+"$@"}

      $ECHO "$0: cannot exec $program $*" 1>&2
      exit 1
    fi
  else
    # The program doesn't exist.
    $ECHO "$0: error: \`$progdir/$program' does not exist" 1>&2
    $ECHO "This script is just a wrapper for $program." 1>&2
    echo "See the libtool documentation for more information." 1>&2
    exit 1
  fi
fi