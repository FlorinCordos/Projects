import java.util.ArrayList;
import java.util.List;

public class Customer {
    private String firstName;
    private String surName;
    private List<Car> carsOwned;


    public Customer(String firstName, String surName) {
        this.firstName = firstName;
        this.surName = surName;
        carsOwned = new ArrayList<>();
    }
    public void buyCar(Dealership dealership,Car selectedCar){
        if(dealership.getInventory().contains(selectedCar)){
            dealership.getInventory().remove(selectedCar);
            if(selectedCar.getFuelType().equals("diesel"))
            {
                dealership.setDieselCars(dealership.getDieselCars()-1);
            }
            else{
                dealership.setGasolineCars(dealership.getGasolineCars()-1);
            }
            carsOwned.add(selectedCar);
        }

        else{
            System.out.println("This car is not available");
        }
    }

    public void buyAllCars(Dealership dealership){
        carsOwned.addAll(dealership.getInventory());
        dealership.getInventory().clear(); //de ce nu merge cu set
        dealership.setGasolineCars(0);
        dealership.setDieselCars(0);
    }

    public void showDetails(){
        System.out.println(ColorConstants.YELLOW+"The customer: "+surName+" "+firstName+" owns:"+ColorConstants.RESET);
        if(carsOwned.size()==0){
            System.out.println("0 cars");
        }
        for (Car car : carsOwned) {
            System.out.println(car.getProducer()+" "+car.getModel());
            //car.getCarDetails();
        }
    }
}
