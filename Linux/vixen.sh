#!/bin/bash

option=$1
input=$2
input2=$3
directory=/home/debunez/Development/VixenEngine
makefile_dir=/home/debunez/Development/VixenEngine/Linux
include_dir=/home/debunez/Development/VixenEngine/include
source_dir=/home/debunez/Development/VixenEngine/source
exec_name=vtest

#Handle find command, -f
if [ "$option" == "-f" ]; then
  grep -rnw "$include_dir" -e "$2"
  grep -rnw "$source_dir" -e "$2"
fi

#Handle jump to command, -j
if [ "$option" == "-j" ]; then
  cd $directory/
fi

#Handle run command, -run
if [ "$option" == "-run" ]; then
  $makefile_dir/$exec_name
fi

#Handle the print command, -p
if [ "$option" == "-p" ]; then

    #print contents of all libs
    if [ "$input" == "all" ]; then
        #all_count will be used to count every file
        let all_count=0

        #append all files in global include
        target=$include_dir
        shared_files=""
        for f in "$target"/*
            do
                    bname=$(basename $f)
                    if [[ $bname == *.h ]]; then
                        shared_files="$shared_files $bname"
                        let all_count=all_count+1
                    fi
            done

        #append all files in vcore
        target=$include_dir/vcore
        vcore_files=""
        for f in "$target"/*
            do
                bname=$(basename $f)
                vcore_files="$vcore_files $bname"
                let all_count=all_count+1
            done
        #append all files in vgraphics
        target=$include_dir/vgraphics
        vgraphics_files=""
        for f in "$target"/*
            do
                bname=$(basename $f)
                vgraphics_files="$vgraphics_files $bname"
                let all_count=all_count+1
            done
        #append all files in vgame
        target=$include_dir/vgame
        vgame_files=""
        for f in "$target"/*
            do
                bname=$(basename $f)
                vgame_files="$vgame_files $bname"
                let all_count=all_count+1
            done

        echo "SHARED_INCLUDES"
        echo "$shared_files"
        echo ""
        echo "VCORE_INCLUDES"
        echo "$vcore_files"
        echo ""
        echo "VGRAPHICS_INCLUDES"
        echo "$vgraphics_files"
        echo ""
        echo "VGAME_INCLUDES"
        echo "$vgame_files"
        echo ""
        echo "COUNT: $all_count"
    fi

    let all_count=0
    if [ "$input" == "vcore" ]; then
        target=$include_dir/vcore
        let count=0
        for f in "$target"/*
            do
                echo $(basename $f)
                let count=count+1
                let all_count=all_count+1
            done
        echo "Count: $count"
        echo ""

        target=$source_dir/vcore
        let count=0
        for f in "$target"/*
            do
                echo $(basename $f)
                let count=count+1
                let all_count=all_count+1
            done
        echo "Count: $count"
        echo "Total: $all_count"
    fi

    if [ "$input" == "vgraphics" ]; then
        target=$include_dir/vgraphics
        let count=0
        for f in "$target"/*
            do
                echo $(basename $f)
                let count=count+1
            done
        echo "Count: $count"
        echo ""

        target=$source_dir/vgraphics
        let count=0
        for f in "$target"/*
            do
                echo $(basename $f)
                let count=count+1
            done
        echo "Count: $count"
    fi

    if [ "$input" == "vgame" ]; then
        target=$include_dir/vgame
        let count=0
        for f in "$target"/*
            do
                echo $(basename $f)
                let count=count+1
            done
        echo "Count: $count"
        echo ""

        target=$source_dir/vgame
        let count=0
        for f in "$target"/*
            do
                echo $(basename $f)
                let count=count+1
            done
        echo "Count: $count"
    fi
fi

#Handle create command, -c
if [ "$option" == "-c" ]; then
  out_dir=""
  if [ "$input" == "vcore" ]; then
    if [[ $input2 == *.h ]]; then
      out_dir=$include_dir/vcore
      atom $out_dir/$input2
    fi

    if [[ $input2 == *.cpp ]]; then
      out_dir=$source_dir/vcore
      atom $out_dir/$input2
    fi
  fi

  if [ "$input" == "vgraphics" ]; then
    if [[ $input2 == *.h ]]; then
      out_dir=$include_dir/vgraphics
      atom $out_dir/$input2
    fi

    if [[ $input2 == *.cpp ]]; then
      out_dir=$source_dir/vgraphics
      atom $out_dir/$input2
    fi
  fi

  if [ "$input" == "vgame" ]; then
    if [[ $input2 == *.h ]]; then
      out_dir=$include_dir/vgame
      atom $out_dir/$input2
    fi

    if [[ $input2 == *.cpp ]]; then
      out_dir=$source_dir/vgame
      atom $out_dir/$input2
    fi
  fi
fi

#Handle open command, -o
file=""
if [ "$option" == "-o" ]; then
  if [[ $input == *.h ]]; then
    file=$(find "$include_dir" -name "$input")
  fi

  if [[ $input == *.cpp ]]; then
    file=$(find "$source_dir" -name "$input")
  fi

  if [ $file ]; then
    atom $file
  fi
fi

#Handle the build command, -b
#This command will build the vixen libraries using a makefile
if [ "$option" == "-b" ]; then

  if [ "$input" == "vcore" ]; then
    cd $makefile_dir
    make -f $makefile_dir/Makefile vcore
  fi

  if [ "$input" == "vgraphics" ]; then
    cd $makefile_dir
    make -f $makefile_dir/Makefile vgraphics
  fi

  if [ "$input" == "vgame" ]; then
    cd $makefile_dir
    make -f $makefile_dir/Makefile vgame
  fi

  if [ "$input" == "vaudio" ]; then
    cd $makefile_dir
    make -f $makefile_dir/Makefile vaudio
  fi

fi
