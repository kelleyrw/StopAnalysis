#!/bin/bash

# mass_stop_min=100
# mass_stop_max=800
mass_stop_min=300
mass_stop_max=300
mass_stop_step=25
mass_stop_offset=100

# mass_lsp_min=0
# mass_lsp_max=700
mass_lsp_min=50
mass_lsp_max=50
mass_lsp_step=25

sr_min=1
sr_max=6

syst_file="plots/interp/t2tt/t2tt_bdt_hists.root"
card_stem="card"

for (( sr = sr_min; sr <= sr_max; sr++ )) 
do
	for (( ms = mass_stop_min; ms <= mass_stop_max; ms=ms+mass_stop_step )) 
	do 
		for (( ml = mass_lsp_min; ml <= mass_lsp_max; ml=ml+mass_lsp_step )) 
		do
			if [[ $ms -lt $(( ml+mass_stop_offset )) ]]; then 
				continue
			fi
			cmd="stop_create_card --syst $syst_file --mass_stop $ms --mass_lsp $ml --sr $sr --output cards/lands/t2tt/${card_stem}_${ms}_${ml}_sr${sr}.txt"
			echo $cmd
			eval $cmd
		done
	done
done

