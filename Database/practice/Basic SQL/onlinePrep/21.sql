select first_name || ' '|| last_name "Full Name", salary
from EMPLOYEES
where department_id <> 80 and ( salary > 6000 or COMMISSION_PCT is not null)
order by COMMISSION_PCT desc, last_name asc;

select *
from EMPLOYEES
where not (instr(lower(email), lower(replace(last_name, ' ', ''))) > 0); --first name case not checked(case analysis needed)

select sum(8100-salary) needed_money
from EMPLOYEES
where salary < 8100;

select ceil(nvl(COMMISSION_PCT,0)) "IS_COMMISSION_CHARGED?" , count(*) employee_count
from employees
group by ceil(nvl(COMMISSION_PCT,0));


select job_id, max(salary) - min(salary) salary_range
from EMPLOYEES
where job_id is not NULL
group by JOB_ID
having count(EMPLOYEE_ID) > 1
order by salary_range desc;

select 
case 
    when COMMISSION_PCT is null then '0 (NO)'
    else '1 (YES)'
end "IS_COMMISSION_CHARGED?",  count(*) employee_count
from employees
group by case 
    when COMMISSION_PCT is null then '0 (NO)'
    else '1 (YES)'
end;


select min(hire_date)
from employees;
--select min(salary)
--from EMPLOYEES
--where DEPARTMENT_ID >40;

select  round(sum(end_date - start_date)/(365 *count(*)),3) info
from JOB_HISTORY
where job_id ='ST_CLERK';
--group by job_id;

select substr(last_name, instr(last_name, 'a'), length(last_name) - 1) "modified", EMPLOYEE_ID
from EMPLOYEES;


select manager_id, count(EMPLOYEE_ID) count_managed, sum(COMMISSION_PCT * salary) total_commission
from EMPLOYEES
where manager_id is not null
group by MANAGER_ID
having sum(COMMISSION_PCT * salary)  > 0;  

select to_char(hire_date, 'DAY'), count(employee_id)
from employees
group by to_char(hire_date, 'DAY');

select e1.employee_id, first_name || ' ' || last_name name ,salary ,(select count(*) from employees e2
                            where e2.salary < e1.salary) richer_than, (select count(*) from employees e3
                            where e3.salary > e1.salary) poorer_than
from employees e1
where (select count(*) from employees e4 where e4.salary < e1.salary) >= 10 and (select count(*) from employees e6
                            where e6.salary > e1.salary) <= 25
order by employee_id ;

select first_name, lpad(salary, 10, '$') salary, department_id id, replace((select department_name from departments e1 where e1.department_id = e2.department_id), ' ', '') dept_name
from employees e2
where DEPARTMENT_ID between 10 and 90
order by length( replace((select department_name from departments e1 where e1.department_id = e2.department_id), ' ', '')) desc;

select substr(first_name, 1,1) || substr(last_name, 1,1) || ' '|| employee_id employee_code , 
    case 
        when (select max(end_date) from job_history e2 where e2.employee_id = e1.employee_id ) is  NULL THEN months_between( trunc(sysdate, 'MONTH'), trunc(hire_date, 'MONTH'))
        else   months_between(trunc((select max(end_date) from job_history e2 where e2.employee_id = e1.employee_id), 'MONTH'), trunc(hire_date, 'MONTH'))
    end  months_spent
from employees e1;

select substr(first_name,1,1) || '. '|| last_name Full_name, salary * 12 * (1 + nvl(COMMISSION_PCT,0)) yearly_income
from employees
where lower(last_name) like 'm%'
order by yearly_income desc;

select r.region_name, c.country_name, l.location_id, l.city
from regions r, countries c, locations l 
where r.region_id = 3 and r.region_id = c.region_id and c.country_id = l.country_id;

select department_id, count(employee_id)
from EMPLOYEES
group by DEPARTMENT_ID
order by count(employee_id) desc;

select department_id, job_id, count(employee_id) as num_emp, sum(salary) tot_sal
from EMPLOYEES
where department_id is not null and job_id is not null
group by department_id, job_id
order by department_id;

select job_id, max(salary), min(salary), avg(salary) 
from EMPLOYEES
where salary > 5000
group by job_id
having sum(salary) < 50000;

select r.region_name, count(c.country_id) 
from regions r, countries c
where r.region_id = c.REGION_ID
group by r.region_name;

select r.region_name, count(l.location_id)
from regions r, locations l, countries c 
where r.region_id = c.region_id and c.country_id = l.country_id
group by r.region_name;

            

                                 




