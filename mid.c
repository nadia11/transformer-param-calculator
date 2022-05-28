#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "awg.h"
#include "radiator_table.h"
#include "Switchgear.h"
#include "PFI.h"
#define PI 3.1416
#include <math.h>

void SetColorAndBackground(int ForgC, int BackC);

int main()
{
    int swg_prim;
float kva=800,kvar,v_in_line=11,v_out_line=433,k=0.33,v_out_phase,axial_length_prim,radial_length_prim,window_height,axial_height_prim,area_per_strip;
float sec_turn,axial_height_sec,strip_length=15,strip_width,strip_depth,radial_height_sec,stacking_factor=0.97,rounding_off_factor=0.945,frequency=50;
char connection[5]="DYN11",winding_material[6]="copper";
float flux_density=1.6,i_density=1.5,working_i_density,temp_rise=45,avg_temp_rise,tappings1=2.5,tappings2=0.41,conductor_area_prim,conductor_area_sec,i_in_phase,i_out_phase,v_per_turn;
float tapping_turn,plain_disc_no=6,tap_disc_no=2,sec_disc=1,turn_per_disc,turn_per_layer_prim,turn_per_layer_sec,strips_inparallel=6;
float disposition_width=3,disposition_depth=2,core_stack=11;
float core_area,core_diameter,core_weight,core_limb_center,core_density=7.65,width_step1,coil_weight_prim,coil_weight_sec,coil_weight_tot;
float mean_dia_prim,mean_dia_sec,mean_length_ofturn_prim,mean_length_ofturn_sec,spec_gravity_copper=8.9;
float in_dia_prim,out_dia_prim,in_dia_sec,out_dia_sec,resistivity_copper=0.021,winding_res_prim,winding_res_sec;
float tank_length,tank_breadth,tank_width,loadloss_prim,loadloss_sec,loadloss_tot,no_loadloss,guarenteed_loss_tot;
float foot_plate_height=40,foot_plate_insulation=5,length_tot_prim_winding,length_tot_sec_winding,tank_surface_area,unit_length_tube=0.865;
float surface_length_tube,tot_length_tube,loss_surface_area,radiator_loss_dissipation,center_distance_radiator,no_of_fins;
float elliptical_tube_no,radiator_bank_no=7,no_of_tube_ineach_bank;
float core_lami_thickness=0.27,step_width,step_length,step_stack,no_of_pieces,step_weight,step_stack_previous;
float no_of_step,no_of_phase=3;
float tot_step_stack,tot_no_of_pieces,tot_weightA,tot_weightB,tot_weightC,core_weight_actual,wire_size_d_primary;
float percent_resistance,percent_reactance,percent_impedence,efficiency;
float tank_volume,oil_volume,core_assembly_volume,copper_volume,core_volume,radiator_oil_volume,conservator_oil_volume,oil_volume_tank,heater_oil_volume;
float conservator_volume,conductor_area_prim_proposed,prim_turn,prim_layer_no=17,sec_layer_no=2,rad_center_distance;
float rad_excess_oil_temp=45,loss_per_fin,correction_factor=0.81;
float contractor_UIF,tank_area,breaker_price_LT,breaker_price_HT,bushing_price,capacitor_price,busbar_Price,contractor_price,PFI_Panel_Price;
float LT_Panel_price,HT_Panel_price,Total_HTLT_Panel_price,heat_chamber_costing,busbar_price_pfi;
float transformer_total_cost,PFI_total_cost,vcb_11KV_price,distribution_trans_kva;

//distribution_trans_kva=kva/4;

//    printf("Enter kva rating:");
//    //scanf("%f", &kva);
//     printf("Enter primary voltage in KV:");
//    //scanf("%f", &v_in_line);
//     printf("Enter secondary voltage in volts:");
//    //scanf("%f", &v_out_line);
//     printf("Enter no.of phase:");
////    scanf("%d", &no_of_phase);
//     printf("Enter connection type ex.Dyn11:  ");
////    scanf("%s", &connection);
//     printf("Enter type of winding material:");
////    scanf("%s", &winding_material);
//      printf("Enter tappings on HV in percentage:");
////    scanf("%f", &tappings1);
//    printf("-");
////      scanf("%f", &tappings2);
//    printf("Enter flux density in Tesla:");
////    scanf("%f", &flux_density);
//    printf("Enter current density in A/mm2:");
//    scanf("%f", &i_density);
//        printf("Enter value of constant K ");
//    scanf("%f", &k);
//    printf("Enter temperature rise range in degree celcius:");
//    scanf("%f", &temp_rise);
//
//    printf("Design of %d KVA transformer:\n ",kva);
//    printf("Primary coil\n");
//printf("Enter no.of plain disc:");
//   scanf("%d", &plain_disc_no);
//   printf("Enter no.of tap disc:");
//   scanf("%d", &tap_disc_no);
//printf("Estimating core window height:\n");
//printf("No.of layers in primary winding");
//   scanf("%d", &prim_layer_no);
//printf("Design of secondary coil");
//printf("Enter how many secondary strips along width for disposition");
//scanf("%d", &disposition_width);
//printf("Enter how many secondary strips along depth for disposition");
//scanf("%d", &disposition_depth);
//printf("Enter strip lenth");
//scanf("%f", &strip_length);
//printf("Core diameter:\n");
//printf("Enter stacking factor");
//scanf("%f", &stacking_factor);
//printf("Enter no.of step for core stack");
//scanf("%d", &core_stack);
//printf("Enter density of core material");
//scanf("%d", &core_density);
//printf("Tank design:\n");
//printf("radiator design");
//printf("Enter height of foot plate");
//scanf("%f", &foot_plate_height);
//printf("Enter foot plate insulation width");
//scanf("%f", &foot_plate_insulation);
//printf("Enter unit length of elliptical tube");
//scanf("%f", &unit_length_tube);
//printf("Enter no.of radiator bank");
//scanf("%d", &radiator_bank_no);
printf("Design of %0.0f kva transformer %0.0f %0.2f\n\n",v_out_phase,i_out_phase);
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

wire_size_d_primary=sqrt((conductor_area_prim*4.0)/PI)+0.04;
printf("wire diameter of primary=%0.2f mm\n",wire_size_d_primary);

wire_size_d_primary=wire_size_d_primary+0.1;


    printf("wire diameter of primary=%0.1f mm\n",wire_size_d_primary);
    swg_prim=awg(wire_size_d_primary);

conductor_area_prim_proposed=(pow(wire_size_d_primary,2))*PI/4;
printf("conductor_area_primary proposed=%0.5f mm2\n",conductor_area_prim_proposed);

//working_i_density=i_in_phase/(0.7854*pow(wire_size_d_primary,2));
//printf("Working current density=%0.4f A/mm2\n",working_i_density);

working_i_density=i_in_phase/conductor_area_prim_proposed;
printf("Working current density=%0.6f A/mm2\n",working_i_density);

v_per_turn=k*sqrt(kva);
printf("Voltage per turn=%0.4f\n",v_per_turn);

sec_turn=round((v_out_line/(sqrt(3))/v_per_turn));
printf("No of secondary turn=%0.0f\n",sec_turn);

v_out_phase=v_out_line/sqrt(3);
printf("Output phase voltage=%0.2f volt\n",v_out_phase);

prim_turn=round(v_in_line*1000*sec_turn/v_out_phase);
printf("No of primary turn at normal tapping=%0.0f\n",prim_turn);

tapping_turn=round(prim_turn*tappings1/100)+1;
printf("No of turns in tapping=%0.0f\n",tapping_turn);

prim_turn=round(prim_turn+tapping_turn);
printf("Total primary turn=%0.0f\n",prim_turn);

turn_per_disc=(prim_turn/(plain_disc_no+tap_disc_no));
printf("Turn per primary disc=%0.0f\n",turn_per_disc);
printf("Covered thickness twoards dpc=0.35mm\n");
printf("Gap between two consecutive conductor=0.05mm");
printf("Working Tolerance=0.1mm");
printf("No of primary layer=%0.0f\n",prim_layer_no);

turn_per_layer_prim=round(turn_per_disc/prim_layer_no+1);
printf("Turn per layer in primary=%0.0f\n",turn_per_layer_prim);

axial_length_prim=round((wire_size_d_primary+0.4)*turn_per_layer_prim);
printf("Axial length for primary coil=%0.2f mm\n",axial_length_prim);

radial_length_prim=round((wire_size_d_primary+0.5)*prim_layer_no);
printf("Radial length of primary coil=%0.2f mm\n",radial_length_prim);

window_height=8*axial_length_prim+130+(tap_disc_no-1)*15+plain_disc_no*10+30;
printf("W/H=%0.2f mm\n",window_height);

axial_height_prim=window_height-2*12.5;
printf("Total axial height of primary coil=%0.2f mm\n",axial_height_prim);

printf("Gap between yoke to top and bottom coil=50mm\n");
printf("Gap between two consecutive tap coil=15mm\n");
printf("Gap between two consecutive plain coil=10mm\n");


i_out_phase=kva*1000/(v_out_line*sqrt(3));
printf("Phase current of secondary=%0.2f A\n",i_out_phase);

conductor_area_sec=i_out_phase/i_density;
printf("Secondary conductor area=%0.2f mm2\n",conductor_area_sec);

strips_inparallel=disposition_width*disposition_depth;
printf("Disposition of strips=%0.0f * %0.0f\n",disposition_width,disposition_depth);

area_per_strip=conductor_area_sec/strips_inparallel;
printf("Approximate area of each strip=%0.2f mm2\n",area_per_strip);

turn_per_layer_sec=round(sec_turn/sec_layer_no)+2;
//turn_per_layer_sec=round(turn_per_layer_sec);
printf("Turn per layer in secondary winding=%0.0f\n",turn_per_layer_sec);

axial_height_sec=round(axial_height_prim);
printf("Axial height of secondary winding=%0.2f mm\n",axial_height_sec);

strip_width=round(axial_height_sec/(disposition_width*turn_per_layer_sec)-0.6);
printf("Bare Strip width for secondary coil=%0.2f mm\n",strip_width);

strip_depth=round(area_per_strip/strip_width);
printf("Bare Strip depth for secondary coil=%0.2f mm\n",strip_depth);

printf("Covered thickness towards TPC=0.5mm\n");
printf("Gap between two consecutive strip=0.1mm\n");
printf("Total length of end packing=10mm\n");

area_per_strip=strip_depth*strip_width-0.86;
printf("Area per strip for secndary=%0.2f mm2\n",area_per_strip);

working_i_density=i_out_phase/(area_per_strip*(disposition_depth*disposition_width));
printf("Working current density=%0.2f A/mm2\n",working_i_density);

axial_height_sec=axial_height_prim;//round((strip_width+0.6)*disposition_width*turn_per_layer_sec)+10;
printf("Axial height of secondary winding=%0.2f mm\n",axial_height_sec);

radial_height_sec=round((strip_depth+0.6)*disposition_depth*sec_layer_no);
printf("Radial height of secondary coil=%0.2f mm\n",radial_height_sec);

v_per_turn=v_out_phase/sec_turn;
printf("Voltage per turn in secondary=%0.2f V\n",v_per_turn);

core_area=v_per_turn/(4.44*frequency*flux_density*stacking_factor*0.0001);
printf("Core area=%0.2f mm2\n",core_area);

core_diameter=10*sqrt((core_area*4)/(rounding_off_factor*3.1416));
printf("Core diameter=%0.2f mm\n",core_diameter);

printf("Radial clearance between core to LV coil=4mm\n");
printf("Radial clearance between LV & HV coil=12mm\n");

in_dia_sec=round(core_diameter+8);
printf("Inside diameter of secondary coil=%0.2f mm\n",in_dia_sec);

out_dia_sec=in_dia_sec+2*radial_height_sec+2;
printf("Outside diameter of secondary coil=%0.2f mm\n",out_dia_sec);

in_dia_prim=out_dia_sec+24;
printf("Inside diameter of primary coil=%0.2f mm\n",in_dia_prim);

out_dia_prim=in_dia_prim+(2*radial_length_prim)-2;
printf("Outside diameter of primary coil=%0.2f mm\n",out_dia_prim);

core_limb_center=out_dia_prim+15;
printf("Core limb center=%0.2f mm\n",core_limb_center);

width_step1=round(core_diameter-7);
printf("Width of step 1=%0.2f mm\n",width_step1);

core_weight=((3*window_height/10+4*core_limb_center/10)+(2*width_step1/10*0.86))*core_area*core_density*stacking_factor*0.001;
printf("Weight of core=%0.2f kg\n\n",core_weight);

printf("Details of step A\n");
step_width=round(core_diameter-7);
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
step_width=round(core_diameter-7);
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
step_width=round(core_diameter-7);
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

coil_weight_prim=3.15*mean_length_ofturn_prim*conductor_area_prim*spec_gravity_copper*0.000001*prim_turn;
printf("Coil weight for primary winding=%0.2f kg\n",coil_weight_prim);

coil_weight_sec=3.3*mean_length_ofturn_sec*conductor_area_sec*spec_gravity_copper*0.000001*sec_turn;
printf("Coil weight for secondary winding=%0.2f kg\n",coil_weight_sec);

coil_weight_tot=(coil_weight_prim+coil_weight_sec);
printf("Total coil weight for three phase=%0.2f kg\n",coil_weight_tot);

printf("Gap between HV coil to the inside of the tank on length side=40mm\n");
printf("Gap between HV coil to the inside of the tank on width side=50mm\n");
printf("Gap between core yolk to tank bottom=40mm\n");
printf("Gap between core yolk to ratio switch bank=20mm\n");
printf("Height of ratio switch=90mm\n");
printf("Height between ratio switch to inside of tank cover=50mm\n");


tank_length=2*core_limb_center+out_dia_prim+2*40;
printf("Tank length=%0.2fmm\n",tank_length);

tank_breadth=out_dia_prim+2*50;
printf("Tank breadth=%0.2fmm\n",tank_breadth);

tank_width=40+5+window_height+2*width_step1+20+90+50;
printf("Tank height=%0.2fmm\n",tank_width);

winding_res_prim=length_tot_prim_winding*resistivity_copper*0.001/conductor_area_prim;
printf("Winding resistant of primary winding=%0.2f ohm \n",winding_res_prim);

winding_res_sec=length_tot_sec_winding*resistivity_copper/conductor_area_sec;
printf("Winding resistant of secondary winding=%0.2f ohm \n",winding_res_sec);

//winding_res_sec=(length_tot_sec_winding*resistivity_copper*0.001)/conductor_area_sec;
//printf("Winding resistant of secondary winding=%0.2f ohm\n",winding_res_sec);

loadloss_prim=3*winding_res_prim*pow(i_in_phase,2);
printf("Load loss for primary winding=%0.2fwatt\n",loadloss_prim);

loadloss_sec=3*winding_res_sec*pow(i_out_phase,2)/1000;
printf("Load loss for secondary=%0.2fwatt\n",loadloss_sec);

loadloss_tot=1.11*(loadloss_prim+loadloss_sec);//stray loss is 3%
printf("Total load loss=%0.2fwatt\n",loadloss_tot);

no_loadloss=core_weight_actual*1.25;//25%handling factor
printf("No load loss=%0.2f watt\n",no_loadloss);

guarenteed_loss_tot=no_loadloss+loadloss_tot;
printf("Total guarenteed loss=%0.2fwatt\n",guarenteed_loss_tot);



percent_reactance=((7.91*frequency*i_out_phase*pow(sec_turn,2)*3.1416*((mean_dia_prim+mean_dia_sec)/2)))/(v_out_phase*axial_height_prim)*(1.5+((radial_length_prim+radial_height_sec)/30))*0.000001;
printf("Percentage reacteance=%0.2f percent\n",percent_reactance);

percent_resistance=(loadloss_tot/10)/kva;
printf("Percentage resistanse=%0.2f percent\n",percent_resistance);

percent_impedence=sqrt(pow(percent_reactance,2)+pow(percent_resistance,2));
printf("Percentage Impedence=%0.2f percent\n",percent_impedence);

efficiency=kva*100/(kva+(no_loadloss/1000)+(loadloss_tot/1000));
printf("Efficiency=%0.2f percent\n",efficiency);

tank_surface_area=2*(tank_length+tank_breadth)*tank_width*0.000001;//converting from mm2 to m2
printf("total surface area of tank in square meter=%0.2f mm2\n",tank_surface_area);

avg_temp_rise=temp_rise*0.8;
printf("Average temperature rise=%0.2f degree celcius\n",avg_temp_rise);

printf("Unit length of each tube=0.865m\n");

surface_length_tube=2*(75+15)*0.9/1000;//i dont know
printf("Surface length for each tube=%0.2f m\n",surface_length_tube);

elliptical_tube_no=(1/(8.8*surface_length_tube*unit_length_tube))*((guarenteed_loss_tot/avg_temp_rise)-12.5*tank_surface_area);
printf("Total number of elliptical tube required=%0.0f\n",elliptical_tube_no);

no_of_tube_ineach_bank=elliptical_tube_no/radiator_bank_no;
printf("Number of tube in each radiator bank=%0.0f\n",no_of_tube_ineach_bank);

tot_length_tube=radiator_bank_no*no_of_tube_ineach_bank*unit_length_tube;
printf("Total length of radiator tube=%0.2f m\n",tot_length_tube);

loss_surface_area=tank_surface_area*500;
printf("Total loss in surface area=%0.2f watt\n",loss_surface_area);

radiator_loss_dissipation=guarenteed_loss_tot-loss_surface_area;
printf("Loss dissipation in radiator=%0.2f watt\n",radiator_loss_dissipation);

rad_center_distance=tank_width-320;
printf("Radiator center distance=%0.2f mm\n",rad_center_distance);

printf("Radiator excess oil temperature=%0.2f degree celcius\n",rad_excess_oil_temp);

loss_per_fin=finloss45(rad_excess_oil_temp,rad_center_distance);


loss_per_fin=loss_per_fin*correction_factor;
printf("Loss per fin=%0.2f watt\n",loss_per_fin);

no_of_fins=radiator_loss_dissipation/loss_per_fin;
printf("No of fins required=%0.2f\n",no_of_fins);

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

oil_volume=oil_volume_tank+radiator_oil_volume+heater_oil_volume+conservator_oil_volume;
printf("Total Oil required=%0.2f liter\n",oil_volume);

conservator_volume=(oil_volume_tank+radiator_oil_volume)*0.1;
printf("Conservator volume=%0.2f liter\n",conservator_volume);
swg_prim=awg(wire_size_d_primary);


bushing_price=bushing_price_LT(i_out_phase);
printf("Bushing price LT=%0.2f TK\n",bushing_price);

heat_chamber_costing=round(13*72*9);


FILE *fp;

   fp = fopen("G://tu/Transformer_Spec.csv", "w+");
   //fp = fopen("G://tu/breaker.csv", "w+");
   fprintf(fp,"%0.0f kva %0.0f/%0.3fkv %0.0fphase %0.0fHz distribution transformer:,,,,,,,,%0.0f kva %0.0f/%0.3fkv %0.0fphase %0.0fHz distribution transformer:\n\n\n",kva,v_in_line,v_out_line/1000,no_of_phase,frequency,kva,v_in_line,v_out_line/1000,no_of_phase,frequency);
   fprintf(fp,"SL,Description,LT(inner),HT(outer),,,,SL,Name of item,Performance,Remarks\n");
   fprintf(fp,"1,Phase,%0.0f,%0.0f,,,,1,No load loss,%0.2f,\n",no_of_phase,no_of_phase,no_loadloss);
   fprintf(fp,"2,Connection,Star(n),Delta,,,,2,Full load loss,%0.2f,\n",loadloss_tot);
   fprintf(fp,"3,Phase Voltage,%0.2f,%0.2f,,,,3,Percentage resistance,%0.2f,\n",v_out_phase,v_in_line*1000,percent_resistance);
   fprintf(fp,"4,No of winding,%0.0f,%0.0f,,,,4,Percentage reactance,%0.2f,\n",sec_disc,plain_disc_no+tap_disc_no,percent_reactance);
   fprintf(fp,"5,Total Turns,%0.0f,%0.0f,,,,5,percentage impedance,%0.2f,\n",sec_turn,prim_turn,percent_impedence);
   fprintf(fp,"6,Turns/Layer,%0.0f,%0.0f,,,,6,Efficiency unity poewer factor,%0.2f,\n",sec_turn/sec_layer_no,prim_turn/prim_layer_no,efficiency);
   fprintf(fp,"7,Conductor size,%0.0fx%0.0f,%d swg\n",strip_width,strip_depth,awg(wire_size_d_primary));
   fprintf(fp,"8,Conductor insulation,0.35mm(DPC),Super\n");
   fprintf(fp,"9,Conductor Arragement,%0.0fWx%0.0fD\n",disposition_depth,disposition_width);
   fprintf(fp,"10,Type, Spiral, Layer\n");
   fprintf(fp,"11,Winding Length,%0.2f mm,%0.2f mm\n",axial_height_prim,axial_height_sec);
   fprintf(fp,"12,EP(Top & Bottom),10mm,10mm\n");
   fprintf(fp,"13,Axl length,%0.2f mm,%0.2f mm\n",axial_height_prim,axial_height_sec);
   fprintf(fp,"14,Inner Dia,%0.1f mm,%0.1f mm\n",in_dia_sec,in_dia_prim);
   fprintf(fp,"15,outer Dia,%0.1f mm,%0.1f mm\n",out_dia_sec,out_dia_prim,bushing_price,bushing_price*1);
   fprintf(fp,"16,Current density(A/mm2),%0.1f,%0.1f\n",working_i_density,working_i_density);
   fprintf(fp,"17,Weight of copper(kg),%0.2f,%0.2f\n",coil_weight_sec*3,coil_weight_prim*3);
   fprintf(fp,"17,Weight of core(kg),%0.2f\n\n\n",core_weight_actual);
//fprintf(fp,",Full load,%0.2f,\n");
   //fprintf(fp,",1/2 full load,%0.2f,\n");
  // fprintf(fp,",1/4 full load,%0.2f,\n");
  // fprintf(fp,"7,Regulation on full load upf,%0.2f,\n");
   //fprintf(fp,"8,Regulation on full load 0.8 lag,%0.2f,\n");
   fclose(fp);

   FILE *fp1;

        fp1 = fopen("G://tu/Transformer_Coasting.csv", "w+");

   fprintf(fp1,"%0.0f kva %0.0f/%0.3fkv %0.0fphase %0.0fHz distribution transformer:,,,,,,,,%0.0f kva %0.0f/%0.3fkv %0.0fphase %0.0fHz distribution transformer:\n\n\n",kva,v_in_line,v_out_line/1000,no_of_phase,frequency,kva,v_in_line,v_out_line/1000,no_of_phase,frequency);
   fprintf(fp1,"SL,Description,Unit,Quantity,rate,Amount,Remarks\n");
   fprintf(fp1,"1,Silicon Steel,KG,%0.2f,230,%0.2f,\n",core_weight_actual,core_weight_actual*230);
   fprintf(fp1,"2,HT wire,KG,%0.2f,800,%0.2f,\n",coil_weight_prim*3*1.05,coil_weight_prim*3*800);
   fprintf(fp1,"3,LT strip,KG,%0.2f,800,%0.2f,\n",coil_weight_sec*3*1.1,coil_weight_sec*3*800);
   fprintf(fp1,"4,MS channel,FT,,450,,\n");
   fprintf(fp1,"5,Cotton tape,FT,,500,,\n");
   fprintf(fp1,"6,Pass Board 1mm,Pcs,,500,,\n");
   fprintf(fp1,"7,Pass Board 2mm,Pcs,,500,,\n");
    fprintf(fp1,"8,Pass Board 3mm,Pcs,,500,,\n");
   fprintf(fp1,"9,Insulation Paper(0.1mm),Kg,,300,,\n");
   fprintf(fp1,"10,Insulation Paper(0.2mm),Kg,,300,,\n");
   fprintf(fp1,"11,Insulation Paper(0.7mm),Kg,,300,,\n");
   fprintf(fp1,"12,Ampere tube 5nos,Pcs,,300,,\n");
   fprintf(fp1,"13,Aica,Kg,,100,,\n");
   fprintf(fp1,"14,Rubber Gum,lb,,200,,\n");
   fprintf(fp1,"15,Cork sheet,Pcs,,1200,,\n");
   fprintf(fp1,"16,Nutral Bar,lb,,400,,\n");
   fprintf(fp1,"17,Fittings,Set,,12000,,\n");
   fprintf(fp1,"18,Bushing(LT & HT),Set,1,%0.2f,%0.2f,\n",bushing_price,bushing_price*1);
   fprintf(fp1,"19,Tap changer,Pcs,,2800,,\n");
   fprintf(fp1,"20,Transformer oil,Liter,%0.1f,100,%0.0f\n",oil_volume,oil_volume*100);
   fprintf(fp1,"21,Gas,Kg,,100,,\n");
   fprintf(fp1,"22,Oxygen,Kg,,100,,\n");
   fprintf(fp1,"23,Sillica gel,Kg,,100,,\n");
   fprintf(fp1,"24,vernish,Kg,,100,,\n");
   fprintf(fp1,"25,Horn Gap,Kg,,100,,\n");
   fprintf(fp1,"26,Aica,Kg,,100,,\n");
   fprintf(fp1,"27,Tank,Pcs,,100,,\n");
   fprintf(fp1,"28,Core building rod,Ft,,40000,,\n");
   fprintf(fp1,"29,Nut bolt washer,Kg,,50,,\n");
   fprintf(fp1,"30,Thrate tape,Doz,,150,,\n");
   fprintf(fp1,"31,Mfg cost,Tk,,240,,\n");
   fprintf(fp1,"32,Tank,TK,%0.2f,240,%0.2f,\n",tank_surface_area,tank_surface_area*240);
   fprintf(fp1,"33,Radiator,TK,%0.0f,320,%0.0f,\n",no_of_fins,no_of_fins*320);
   fprintf(fp1,"34,Bucholz relay,job,1,25000,25000,\n");
   fprintf(fp1,"35,Temp & oil level guage,job,1,4000,4000,\n");
   fprintf(fp1,"36,LT & HT Lead,nos,25000,7,25000*7,\n");
   fprintf(fp1,"37,Heat chamber costing,per unit,936,%0.0f,,\n",heat_chamber_costing);
     fprintf(fp1,",,,,Total=,,,\n");
       fclose(fp1);

       transformer_total_cost=core_weight_actual*230+coil_weight_tot*800+bushing_price+oil_volume*100+tank_surface_area*240+no_of_fins*320+25000+4000+heat_chamber_costing;

   breaker_price_HT=breaker_Price(i_in_phase);
   printf("HT breaker price=%0.0f TK \n",breaker_price_HT);
   breaker_price_LT=breaker_Price(i_out_phase);
   printf("LT breaker price=%0.0f TK \n",breaker_price_LT);
   LT_Panel_price=LT_panel_price();
   HT_Panel_price=HT_panel_price();
   Total_HTLT_Panel_price=LT_Panel_price+HT_Panel_price;
     printf("LT & HT total panel price=%0.0f TK \n",Total_HTLT_Panel_price);



   FILE *fp2;
   fp2 = fopen("G://tu/33 KV outdoor.csv", "w+");
   fprintf(fp2,",SL,Name of item,Unit,Quantity,Rate,Amount,Remarks\n");
   fprintf(fp2,",1,ACR,Nos,1,1150000,1150000,\n");
   fprintf(fp2,",2,Isolator,Nos,1,130000,130000,\n");
   fprintf(fp2,",3,LA,Nos,1,120000,120000,\n");
   fprintf(fp2,",4,PT(HT),Nos,1,50000,50000,\n");
   fprintf(fp2,",5,CT(HT),Nos,1,50000,50000,\n");
   fprintf(fp2,",6,PT(LT),Nos,1,50000,50000,\n");
   fprintf(fp2,",6,CT(LT),Nos,1,50000,50000,\n");
   fprintf(fp2,",7,33 KV OVCB,Nos,1,750000,750000,\n");
   fprintf(fp2,",8,33/11 KV transformer,Nos,1,%0.0f,%0.0f,\n",transformer_total_cost,transformer_total_cost*1);
   fprintf(fp2,",9,11 KV VCB,Nos,1,750000,750000,\n");
   fprintf(fp2,",10,%0.0f kva distribution transformer,Nos,4,%0.0f,%0.0f,\n",transformer_total_cost,transformer_total_cost*4);
   fprintf(fp2,",11,415 V ACB,Nos,4,750000,750000,\n");
   fprintf(fp2,",12,415 V MCCB,Nos,1,750000,750000,\n");
   fprintf(fp2,",13,PFI Panel,Nos,1,750000,750000,\n");


 fp2 = fopen("G://tu/Switchgear.csv", "w+");
   fprintf(fp2,",1,CT(LT),Nos,1,12500,12500,\n");
   fprintf(fp2,",2,CT(HT),Nos,1,30000,30000,\n");
   fprintf(fp2,",3,VCB HT,Nos,1,%0.2f,%0.2f\n",breaker_price_HT,breaker_price_HT);
    fprintf(fp2,",4,VCB LT,Nos,1,%0.2f,%0.2f\n",breaker_price_LT,breaker_price_LT);
   fprintf(fp2,",5,PT(LT),Nos,1,12500,12500,\n");
     fprintf(fp2,",6,PT(HT),Nos,1,30000,30000,\n");
   fprintf(fp2,",7,IDMT relay,Nos,1,30000,30000,\n");
   fprintf(fp2,",8,Annunciator(12W),Nos,1,20000,20000,\n");
   fprintf(fp2,",9,Hooter,Nos,240\n");
   fprintf(fp2,",10,Mimic,Nos,1,5000,5000,\n");
   fprintf(fp2,",11,Multifunction Meter,Nos,1,23500\n");
   fprintf(fp2,",12,Panel & Manpower costing,Tk,240\n");
   fclose(fp2);

   //PFI calculation
   kvar=kva*0.6;
   printf("KVAR=%0.2f KVR\n",kvar);
   capacitor_price=Capacitor_price(kvar);
   printf("Capacitor price=%0.0f\n\n\n",capacitor_price);


   busbar_price_pfi=3*busbar_price_PFI(kvar);
     printf("Busbar weight for PFI=%0.0f\n",busbar_price_pfi);
    busbar_Price=busbar_price(i_out_phase)*4+busbar_price(i_in_phase)*3;
   printf("Busbar weight for LT and HT=%0.0f\n",busbar_Price);




 PFI_Panel_Price=PFI_panel_price();
   printf("PFI Panel Price=%0.0f\n",PFI_Panel_Price);
     FILE *fp3;
   fp3 = fopen("G://tu/PFI.csv", "w+");
    fprintf(fp3,",SL,Name of item,Unit,Quantity,Rate,Amount,Remarks\n");
   fprintf(fp3,",1,Capacitor,Set,1,%0.0f,%0.0f,\n",capacitor_price,1*capacitor_price);
    fprintf(fp3,",2,Magnetic Contractor,job,,240\n");
     fprintf(fp3,",3,Fuse,job,,240\n");
      fprintf(fp3,",4,Busbar,kg,800,%0.0f,\n");
       fprintf(fp3,",5,APFC relay,job,,240\n");
         fprintf(fp3,",6,Lamp,No's,3,30,3*30,\n");
           fprintf(fp3,",7,Heater,No's,3,3*300,\n");
             fprintf(fp3,",8,Panel,KG,100,800,80000,\n");
   fclose(fp3);
  capacitor_bank (kvar);
  contractor_price=Mag_Contractor_price(kvar);
   printf("Contractor price=%0.0f\n",axial_length_prim);
   printf("Design of  kva transformer %d %0.2f\n\n",awg(2.3),i_out_phase);

    return 0;
}
void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
