#!/bin/bash

scp /home/mamiemal/DO6_CICD-1/builds/aUVaMoap/0/students/DO6_CICD.ID_356283/mamiemal_student.21_school.ru/DO6_CICD-1/src/cat/s21_cat mami@10.10.0.2:/usr/local/bin/

scp /home/mamiemal/DO6_CICD-1/builds/aUVaMoap/0/students/DO6_CICD.ID_356283/mamiemal_student.21_school.ru/DO6_CICD-1/src/grep/s21_grep mami@10.10.0.2:/usr/local/bin/ 

ssh mami@10.10.0.2 ls /usr/local/bin