#!/bin/bash

~/Programs/tools/bbmap/bbduk.sh -Xmx2g in="*_read1.fastq"  in2="*_read2.fastq" outm="*_read1_trimmed.fastq" outm2="*_read2_trimmed.fastq" ref="bbmap/resources/adapters.fa" k=25 mink=10 hdist=2 hdist2=0 tpe tbo mkh=3 ktrim=r 
