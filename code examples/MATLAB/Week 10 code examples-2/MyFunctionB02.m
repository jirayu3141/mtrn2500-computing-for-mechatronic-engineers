% a usual function, which we call using its handle ( ~ function pointer )
function r=MyFunctionB02(a)
    disp('here is MyFunctionB02()');
    disp(a);
    r=1+int32(a(1))+1000;
end