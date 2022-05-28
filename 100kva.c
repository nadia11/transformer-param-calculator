#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//#include "Untitled3.h"

#define PI 3.1416
#include <math.h>

void SetColorAndBackground(int ForgC, int BackC);

int main()
{
    int swg_prim;
float kva=150,kvar,v_in_line=11,v_out_line=415,k=0.41,v_out_phase,axial_length_prim,radial_length_prim,window_height,axial_height_prim,area_per_strip;
float sec_turn,axial_height_sec,strip_length=15,strip_width,strip_depth,radial_height_sec,stacking_factor=0.97,rounding_off_factor=0.945,frequency=50;
char connection[5]="DYN11",winding_material[6]="copper";
float flux_density=1.6,i_density=3.5,working_i_density,temp_rise=45,avg_temp_rise,tappings1=5,tappings2=2.5,conductor_area_prim,conductor_area_sec,i_in_phase,i_out_phase,v_per_turn;
float tapping_turn,plain_disc_no=4,tap_disc_no=0,sec_disc=0,turn_per_disc_prim,turn_per_disc_sec,turn_per_layer_prim,turn_per_layer_sec,strips_inparallel=2;
float disposition_width=1,disposition_depth=2,core_stack=11;
float core_area,core_diameter,core_weight,core_limb_center,core_density=7.65,width_step1,coil_weight_prim,coil_weight_sec,coil_weight_tot;
float mean_dia_prim,mean_dia_sec,mean_length_ofturn_prim,mean_length_ofturn_sec,spec_gravity_copper=8.9;//8.9
float in_dia_prim,out_dia_prim,in_dia_sec,out_dia_sec,resistivity_copper=0.021/*0.021*/,winding_res_prim,winding_res_sec;
float tank_length,tank_breadth,tank_width,loadloss_prim,loadloss_sec,loadloss_tot,no_loadloss,guarenteed_loss_tot;
float foot_plate_height=40,foot_plate_insulation=5,length_tot_prim_winding,length_tot_sec_winding,tank_surface_area,unit_length_tube=0.590;
float surface_length_tube,tot_length_tube,loss_surface_area,radiator_loss_dissipation,center_distance_radiator,no_of_fins;
float elliptical_tube_no,radiator_bank_no=7,no_of_tube_ineach_bank;
float core_lami_thickness=0.27,step_width,step_length,step_stack,no_of_pieces,step_weight,step_stack_previous;
float no_of_step,no_of_phase=3;
float tot_step_stack,tot_no_of_pieces,tot_weightA,tot_weightB,tot_weightC,core_weight_actual,wire_size_d_primary;
float percent_resistance,percent_reactance,percent_impedence,efficiency;
float tank_volume,oil_volume,core_assembly_volume,copper_volume,core_volume,radiator_oil_volume,conservator_oil_volume,oil_volume_tank,heater_oil_volume;
float conservator_volume,conductor_area_prim_proposed,prim_turn,prim_layer_no=17,sec_layer_no=2,rad_center_distance;
float rad_excess_oil_temp=40,loss_per_fin,correction_factor=0.9;
float contractor_UIF,tank_area,breaker_price_LT,breaker_price_HT,bushing_price,capacitor_price,busbar_Price,contractor_price,PFI_Panel_Price;
float LT_Panel_price,HT_Panel_price,Total_HTLT_Panel_price,heat_chamber_costing,busbar_price_pfi;
float transformer_total_cost,PFI_total_cost,vcb_11KV_price,distribution_trans_kva,frac_part;
float wire_length_prim,wire_width_prim,turn_per_disc_sec_frac,turn_per_disc_prim_plain,turn_per_disc_prim_tap,wire_length_tap,wire_width_tap;



printf("Design of %0.0f kva transformer \n\n",kva);
//SetColorAndBackground(10,4);
printf("No load voltage ratio %0.0f kv/%0.0f volt\n",v_in_line,v_out_line);
printf("No of phase/frequency:%0.0f/%0.2f Hz\n",no_of_phase,frequency);
printf("Connection type DYN11\n");
printf("Winding material:Electrolytic copper\n");
printf("Tappings on HV +-%0.2f  +- %0.2f percent \n",tappings2,tappings1);
printf("Maximum flux density %0.2f tesla\n",flux_density);
printf("Maximum current density %0.2f in A/mm2\n",i_density);
printf("Temperature rise %0.1f degree celcius\n",temp_rise);
printf("Transposition is placed at the center of the coil\n");
printf("Grade of core=27-M4\n");


i_in_phase=kva/(3*v_in_line);
printf("V_input_phase=%0.2f kv\n",v_in_line);
printf("I_input_phase=%0.2f A\n",i_in_phase);


conductor_area_prim=i_in_phase/i_density;
printf("conductor_area_primary=%0.5f mm2\n",conductor_area_prim);
wire_size_d_primary=sqrt((conductor_area_prim*4.0)/3.1416)+0.14;
//printf("wire diameter of primary=%0.2f mm\n",wire_size_d_primary);

//wire_size_d_primary=wire_size_d_primary+0.1;


    printf("wire diameter of primary=%0.3f mm\n",wire_size_d_primary);
//    swg_prim=awg(wire_size_d_primary);

conductor_area_prim_proposed=(pow(wire_size_d_primary,2))*3.1416/4;
printf("conductor_area_primary proposed=%0.5f mm2\n",conductor_area_prim_proposed);

//working_i_density=i_in_phase/(0.7854*pow(wire_size_d_primary,2));
//printf("Working current density=%0.4f A/mm2\n",working_i_density);

working_i_density=i_in_phase/conductor_area_prim_proposed;
printf("Working current density=%0.6f A/mm2\n",working_i_density);

v_per_turn=k*sqrt(kva);
printf("Voltage per turn=%0.4f\n",v_per_turn);

sec_turn=round(((v_out_line/sqrt(3))/v_per_turn));
printf("No of secondary turnhhh=%0.3f\n",sec_turn);

v_out_phase=v_out_line/sqrt(3);
printf("Output phase voltage=%0.2f volt\n",v_out_phase);

prim_turn=round(v_in_line*1000*sec_turn/v_out_phase);
printf("No of primary turn at normal tapping=%0.0f\n",prim_turn);

tapping_turn=round(prim_turn*tappings1/100);
printf("No of turns in tapping=%0.0f\n",tapping_turn);

prim_turn=round(prim_turn+tapping_turn)+1;
printf("Total primary turn=%0.0f\n",prim_turn);

turn_per_disc_sec=(sec_turn/sec_disc);
printf("Turn per disc=%0.0f\n",turn_per_disc_sec);

turn_per_disc_sec_frac=turn_per_disc_sec-floor(turn_per_disc_sec);
printf("Turn per Secondary disc=%0.0fand%0.0f/12\n",floor(turn_per_disc_sec),round(12*turn_per_disc_sec_frac));



turn_per_disc_prim=(prim_turn/plain_disc_no);
printf("Turn per primary disc=%0.0f\n",turn_per_disc_prim);
printf("Covered thickness twoards dpc=0.35mm\n");
printf("Gap between two consecutive conductor=0.05mm");
printf("Working Tolerance=0.1mm");
printf("No of primary layer=%0.0f\n",prim_layer_no);

turn_per_layer_prim=round(turn_per_disc_prim/prim_layer_no+1);
printf("Turn per layer in primary=%0.0f\n",turn_per_layer_prim);

axial_length_prim=((wire_size_d_primary+0.25)*turn_per_layer_prim);
printf("Axial length for primary coil=%0.2f mm\n",axial_length_prim);

radial_length_prim=((wire_size_d_primary+0.35)*prim_layer_no);
printf("Radial length of primary coil=%0.2f mm\n",radial_length_prim);

window_height=axial_length_prim*plain_disc_no+74;
printf("W/H=%0.2f mm\n",window_height);

axial_height_prim=window_height-2*10;
printf("Total height available for secondary winding=%0.2f mm\n",axial_height_prim);




i_out_phase=kva*1000/(v_out_line*sqrt(3));
printf("Phase current of secondary=%0.2f A\n",i_out_phase);

conductor_area_sec=i_out_phase/(working_i_density)/disposition_depth;
printf("Secondary conductor area=%0.2f mm2\n",conductor_area_sec);

strips_inparallel=disposition_width*disposition_depth;
printf("Disposition of strips=%0.0f * %0.0f\n",disposition_width,disposition_depth);


//area_per_strip=conductor_area_sec/strips_inparallel;
printf("Approximate area of each strip=%0.0fx%0.1fx2 mm2\n",strip_width,strip_depth);

turn_per_layer_sec=round(sec_turn/sec_layer_no)+2;
//turn_per_layer_sec=round(turn_per_layer_sec);
printf("Turn per layer in secondary winding=%0.0f\n",turn_per_layer_sec);

strip_width=(((axial_height_prim/turn_per_layer_sec)-1.5));
printf("Strip width for secondary coil=%0.3f mm\n",strip_width);

strip_depth=round((conductor_area_sec/strip_width)+0.44);
printf("Bare Strip depth for secondary coil=%0.2f mm\n",strip_depth);

printf("Covered thickness towards TPC=0.4mm\n");
printf("Gap between two consecutive strip=0.1mm\n");
//printf("Total length of end packing=10mm\n");

area_per_strip=(strip_depth*strip_width*2)-0.86;
printf("Area per strip for secndary=%0.2f mm2\n",area_per_strip);

working_i_density=i_out_phase/(area_per_strip);
printf("Working current density=%0.2f A/mm2\n",working_i_density);

axial_height_sec=(strip_width+0.5)*disposition_width*turn_per_layer_sec+10;//round((strip_width+0.6)*disposition_width*turn_per_layer_sec)+10;
printf("Axial height of secondary winding=%0.2f mm\n",axial_height_sec);

radial_height_sec=round((strip_depth+0.5)*disposition_depth*sec_layer_no);
printf("Radial height of secondary coil=%0.2f mm\n",radial_height_sec);

v_per_turn=v_out_phase/sec_turn;
printf("Voltage per turn in secondary=%0.2f V\n",v_per_turn);

core_area=v_per_turn/(4.44*frequency*flux_density*stacking_factor*0.0001);
printf("Core area=%0.2f mm2\n",core_area);

core_diameter=10*sqrt((core_area*4)/(rounding_off_factor*3.1416));
printf("Core diameter=%0.2f mm\n",core_diameter);

printf("Radial clearance between core to LV coil=4mm\n");
printf("Radial clearance between LV & HV coil=12mm\n");

in_dia_sec=(core_diameter+6);
printf("Inside diameter of secondary coil=%0.2f mm\n",in_dia_sec);

out_dia_sec=in_dia_sec+2*radial_height_sec;
printf("Outside diameter of secondary coil=%0.2f mm\n",out_dia_sec);

in_dia_prim=out_dia_sec+13;
printf("Inside diameter of primary coil=%0.2f mm\n",in_dia_prim);

out_dia_prim=in_dia_prim+(2*radial_length_prim);
printf("Outside diameter of primary coil=%0.2f mm\n",out_dia_prim);

core_limb_center=out_dia_prim+13;
printf("Core limb center=%0.2f mm\n",core_limb_center);

width_step1=round(core_diameter-3);
printf("Width of step 1=%0.2f mm\n",width_step1);

core_weight=((3*window_height/10+4*core_limb_center/10)+(2*width_step1/10*0.86))*core_area*core_density*stacking_factor*0.001;
printf("Weight of core=%0.2f kg\n\n",core_weight);

printf("Details of step A\n");
step_width=round(core_diameter-9);
step_stack_previous=0;
tot_step_stack=0;
tot_no_of_pieces=0;
tot_weightA=0;
printf("Step_no   width  length    stack      piece       Weight\n");
printf("           mm      mm       mm                      kg\n\n");
for (no_of_step= 1; no_of_step< 10; no_of_step++) {

    step_stack=sqrt(pow(core_diameter,2)-pow(step_width,2))-step_stack_previous;
     step_stack_previous=sqrt(pow(core_diameter,2)-pow(step_width,2));
    step_length=(window_height+2*step_width)/10;
    no_of_pieces=step_stack/core_lami_thickness;
    step_weight=(step_length-(step_width/10))*step_width*step_stack/10*7.65*stacking_factor*0.0001*2;
    tot_step_stack=step_stack+tot_step_stack;
    tot_no_of_pieces=no_of_pieces+tot_no_of_pieces;
    tot_weightA=step_weight+tot_weightA;
    printf("%0.0f\t %0.2f\t %0.2f\t 2* %3.2f     %0.2f\t %0.2f\n", no_of_step,step_width,step_length*10,step_stack,2*no_of_pieces,step_weight);
    step_width=step_width-10;

}
printf("\t\t  total\t 2*%0.2f   %0.2f      %0.2f\t \n\n",tot_step_stack,2*tot_no_of_pieces,tot_weightA);


printf("Details of step B\n");
step_width=round(core_diameter-3);
step_stack_previous=0;
tot_step_stack=0;
tot_no_of_pieces=0;
tot_weightB=0;
printf("Step_no   width  length    stack      piece       Weight\n");
printf("           mm      mm       mm                      kg\n\n");
for (no_of_step= 1; no_of_step< 10; no_of_step++) {

    step_stack=sqrt(pow(core_diameter,2)-pow(step_width,2))-step_stack_previous;
     step_stack_previous=sqrt(pow(core_diameter,2)-pow(step_width,2));
    step_length=(window_height+step_width);
    no_of_pieces=step_stack/core_lami_thickness;
    step_weight=((step_length/10)-(step_width/20))*step_width/10*step_stack/10*7.65*stacking_factor*0.001;
       tot_step_stack=step_stack+tot_step_stack;
    tot_no_of_pieces=no_of_pieces+tot_no_of_pieces;
    tot_weightB=step_weight+tot_weightB;
    printf("%0.0f\t %0.2f\t %0.2f\t  %3.2f     %0.2f\t %0.2f\n", no_of_step,step_width,step_length,step_stack,no_of_pieces,step_weight);
    //printf("%d\t %0.2f\t %0.2f\t %0.2f\t %0.2f\t %0.2f\n", no_of_step,step_width,step_length,step_stack,no_of_pieces,step_weight);
    step_width=step_width-10;

}
printf("\t\t  total\t %0.2f   %0.2f         %0.2f\t \n\n",tot_step_stack,tot_no_of_pieces,tot_weightB);
//printf("\t\ttotal\t %0.2f\t %0.2f\t %0.2f\t \n\n",tot_step_stack,tot_no_of_pieces,tot_weightB);


printf("Details of step C\n");
step_width=round(core_diameter-3);
step_stack_previous=0;
tot_step_stack=0;
tot_no_of_pieces=0;
tot_weightC=0;
printf("Step_no   width  length    stack      piece       Weight\n");
printf("           mm      mm       mm                      kg\n\n");
for (no_of_step= 1; no_of_step< 10; no_of_step++) {

    step_stack=sqrt(pow(core_diameter,2)-pow(step_width,2))-step_stack_previous;
     step_stack_previous=sqrt(pow(core_diameter,2)-pow(step_width,2));
    step_length=(2*core_limb_center+step_width);
    no_of_pieces=step_stack/core_lami_thickness;
    step_weight=((((step_length/10)-(step_width/10))*step_width/10)-pow(step_width/20,2))*step_stack/10*7.65*stacking_factor*0.001*2;
       tot_step_stack=step_stack+tot_step_stack;
    tot_no_of_pieces=no_of_pieces+tot_no_of_pieces;
    tot_weightC=step_weight+tot_weightC;
    printf("%0.0f\t %0.2f\t %0.2f  2* %3.2f     %0.2f\t %0.2f\n", no_of_step,step_width,step_length,step_stack,no_of_pieces,step_weight);
    //printf("%d\t %0.2f\t %0.2f\t %0.2f\t %0.2f\t %0.2f\n", no_of_step,step_width,step_length,step_stack,no_of_pieces,step_weight);
    step_width=step_width-10;

}
printf("\t\t  total\t  2*%0.2f   %0.2f    %0.2f\t \n\n",tot_step_stack,2*tot_no_of_pieces,tot_weightC);
//printf("\t\ttotal\t %0.2f\t %0.2f\t %0.2f\t \n\n",tot_step_stack,tot_no_of_pieces,tot_weightC);
core_weight_actual=tot_weightA+tot_weightB+tot_weightC;
printf("Core weight actual=%0.2f kg\n",core_weight_actual);




mean_dia_prim=(in_dia_prim+out_dia_prim)/2;
printf("Mean diameter for primary winding=%0.2f mm\n",mean_dia_prim);

mean_dia_sec=(in_dia_sec+out_dia_sec)/2;
printf("Mean diameter for secondary winding=%0.2f mm\n",mean_dia_sec);

mean_length_ofturn_prim=mean_dia_prim*3.1416;
printf("Mean length of turn for primary winding=%0.2f mm\n",mean_length_ofturn_prim);

length_tot_prim_winding=mean_length_ofturn_prim*prim_turn;
printf("Total length of primary winding=%0.2f mm\n",length_tot_prim_winding);

mean_length_ofturn_sec=mean_dia_sec*3.1416;
printf("Mean length of turn for secondary coil=%0.2f mm\n",mean_length_ofturn_sec);

length_tot_sec_winding=mean_length_ofturn_sec*sec_turn;
printf("Total length of secondary winding=%0.2f mm\n",length_tot_sec_winding);

coil_weight_prim=round(3.42*mean_length_ofturn_prim*conductor_area_prim*spec_gravity_copper*0.000001*prim_turn);
printf("Coil weight for primary winding=%0.2f kg\n",coil_weight_prim);

coil_weight_sec=round(3.21*mean_length_ofturn_sec*conductor_area_sec*spec_gravity_copper*0.000001*2*(sec_turn-2));
printf("Coil weight for secondary winding=%0.2f kg\n",coil_weight_sec);

coil_weight_tot=(coil_weight_prim+coil_weight_sec);
printf("Total coil weight for three phase=%0.2f kg\n",coil_weight_tot);

//printf("Gap between HV coil to the inside of the tank on length side=40mm\n");
//printf("Gap between HV coil to the inside of the tank on width side=50mm\n");
//printf("Gap between core yolk to tank bottom=40mm\n");
//printf("Gap between core yolk to ratio switch bank=20mm\n");
//printf("Height of ratio switch=90mm\n");
//printf("Height between ratio switch to inside of tank cover=50mm\n");


tank_length=2*core_limb_center+out_dia_prim+2*25+60;
printf("Tank length=%0.2fmm\n",tank_length);

tank_breadth=out_dia_prim+95;
printf("Tank breadth=%0.2fmm\n",tank_breadth);

tank_width=window_height+2*width_step1+110+105;
printf("Tank height=%0.2fmm\n",tank_width);

winding_res_prim=length_tot_prim_winding*resistivity_copper*0.001/conductor_area_prim;
printf("Winding resistant of primary winding=%0.2f ohm \n",winding_res_prim);

winding_res_sec=length_tot_sec_winding*resistivity_copper/(conductor_area_sec*2);
printf("Winding resistant of secondary winding=%0.2f ohm \n",winding_res_sec);

//winding_res_sec=(length_tot_sec_winding*resistivity_copper*0.001)/conductor_area_sec;
//printf("Winding resistant of secondary winding=%0.2f ohm\n",winding_res_sec);

loadloss_prim=3*winding_res_prim*pow(i_in_phase,2);
printf("Load loss for primary winding=%0.2fwatt\n",loadloss_prim);

loadloss_sec=3*winding_res_sec*pow(i_out_phase,2)/1000;
printf("Load loss for secondary=%0.2fwatt\n",loadloss_sec);

loadloss_tot=(loadloss_prim+loadloss_sec)+100;//stray loss is 3%
printf("Total load loss=%0.2fwatt\n",loadloss_tot);

no_loadloss=core_weight_actual*1.25;//25%handling factor
printf("No load loss=%0.2f watt\n",no_loadloss);

guarenteed_loss_tot=no_loadloss+loadloss_tot;
printf("Total guarenteed loss=%0.2fwatt\n",guarenteed_loss_tot);


axial_height_prim=(axial_height_prim+axial_height_sec)/2;
percent_reactance=((7.91*0.95*frequency*i_out_phase*pow(sec_turn,2)*3.1416*((mean_dia_prim+mean_dia_sec)/2)))/(v_out_phase*axial_height_prim)*(1+((radial_length_prim+radial_height_sec)/30))*0.000001;
printf("Percentage reacteance=%0.2f percent\n",percent_reactance);

percent_resistance=(loadloss_tot/10)/kva;
printf("Percentage resistanse=%0.2f percent\n",percent_resistance);

percent_impedence=sqrt(pow(percent_reactance,2)+pow(percent_resistance,2));
printf("Percentage Impedence=%0.2f percent\n",percent_impedence);

efficiency=100*(kva*0.8/(kva*0.8+(no_loadloss/1000)+(loadloss_tot*0.64/1000)));
printf("Efficiencyat 0.8 pf=%0.2f percent\n",efficiency);

tank_surface_area=2*(tank_length+tank_breadth)*tank_width*0.000001;//converting from mm2 to m2
printf("total surface area of tank in square meter=%0.2f mm2\n",tank_surface_area);

avg_temp_rise=temp_rise*0.8;
printf("Average temperature rise=%0.2f degree celcius\n",avg_temp_rise);

printf("Unit length of each tube=0.590m\n");

surface_length_tube=2*(75+15)*0.9/1000;//i dont know
printf("Surface length for each tube=%0.2f m\n",surface_length_tube);

elliptical_tube_no=(1/(8.8*surface_length_tube*unit_length_tube))*((guarenteed_loss_tot/avg_temp_rise)-12.5*tank_surface_area);
printf("Total number of elliptical tube required=%0.3f\n",elliptical_tube_no);

no_of_tube_ineach_bank=elliptical_tube_no/radiator_bank_no;
printf("Number of tube in each radiator bank=%0.0f\n",no_of_tube_ineach_bank);

tot_length_tube=radiator_bank_no*no_of_tube_ineach_bank*unit_length_tube;
printf("Total length of radiator tube=%0.2f m\n",tot_length_tube);



//volume of oil calculation
tank_volume=tank_breadth*tank_length*tank_width*0.000001;
printf("tank volume=%0.2f\n",tank_volume);

core_volume=core_weight_actual/7.65;
printf("Core volume=%0.2f liter\n",core_volume);

copper_volume=(coil_weight_tot)/8.96;
printf("Copper volume=%0.2f liter\n",copper_volume);

core_assembly_volume=core_volume+copper_volume+32.8;

oil_volume_tank=tank_volume-core_assembly_volume;
printf("Oil required in tank=%0.2f liter\n",oil_volume_tank);


radiator_oil_volume=tot_length_tube*0.9;
printf("Oil required in radiator=%0.2f liter\n",radiator_oil_volume);

heater_oil_volume=0.06*kva;
printf("Oil required in heater=%0.2f liter\n",heater_oil_volume);

conservator_oil_volume=(oil_volume_tank+radiator_oil_volume)*0.1/3;
printf("Oil required in conservetor=%0.2f liter\n",conservator_oil_volume);

oil_volume=oil_volume_tank+radiator_oil_volume+heater_oil_volume+conservator_oil_volume+7;
printf("Total Oil required=%0.2f liter\n",oil_volume);

conservator_volume=(oil_volume_tank+radiator_oil_volume)*0.1;
printf("Conservator volume=%0.2f liter\n",conservator_volume);





    return 0;
}
void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
