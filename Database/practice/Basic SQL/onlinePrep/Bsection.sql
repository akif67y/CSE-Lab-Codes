select substr(phone_number, 1, instr(PHONE_NUMBER, '.') -1) country_code, count(employee_id) number_of_employees
from employees
where hire_date > to_date('01-JAN-2005', 'DD-MON-YYYY')
group by substr(phone_number, 1, instr(PHONE_NUMBER, '.') -1);

select employee_id, salary, abs(round(salary/1000,0) * 1000 - salary) salary_diff
from EMPLOYEES;

create table emp_training
(
    training_id number(6,0) constraint tr_pk primary key,
    employee_id number(6,0),
    training_name varchar2(50) not null,
    reg_date date default sysdate,
    constraint te_k foreign key(employee_id) references employees(employee_id)
);
insert into EMP_TRAINING values (1, 180, 'conflict resolution', to_date('01-JAN-2005', 'DD-MON-YYYY'));
commit;

select DEPARTMENT_ID, to_char(sum(salary * 12) , '99,999,999') total_annual_payout
from employees
group by DEPARTMENT_ID
having count(employee_id) > 2 and min(salary) >= 2500;

select employee_id, upper(substr(first_name, 1, 2)) || length(last_name) || substr(phone_number, length(PHONE_NUMBER), 1) as "security code"
from EMPLOYEES
where length(first_name) > length(last_name)
order by length("security code") desc;

SELECT 
    -- Standard human-readable format
    TO_CHAR(SYSDATE, 'DD-MON-YYYY HH24:MI:SS') AS "Standard",
    
    -- Using FM and Ordinals
    TO_CHAR(SYSDATE, 'fmDay, "the" DDth "of" Month, YYYY') AS "Verbose",
    
    -- ISO standard for data export
    TO_CHAR(SYSDATE, 'YYYY-MM-DD"T"HH24:MI:SS') AS "ISO_Format"
FROM DUAL;

select last_name
from EMPLOYEES
where first_name like '%'|| first_name || '%';


