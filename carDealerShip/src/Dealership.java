import java.util.ArrayList;
import java.util.List;

class Dealership {
   private int dieselCars=0;
   private int gasolineCars=0;
   public int getDieselCars() {
        return dieselCars;
    }
    public int getGasolineCars() {
        return gasolineCars;
    }


    private List<Car> inventory;

    public Dealership() {
        inventory = new ArrayList<>();
    }
    public List<Car> getInventory() {
        return inventory;
    }

    public void addCar(Car car) {
        inventory.add(car);
        if(car.getFuelType().equals("diesel")){
            dieselCars++;
        }
        else if(car.getFuelType().equals("gasoline")){
            gasolineCars++;
        }
    }
    void addCar(Car car, int n){
        for (int i=1;i<=n;i++) {
            inventory.add(car);
            if(car.getFuelType().equals("diesel")){
                dieselCars++;
            }
            else if(car.getFuelType().equals("gasoline")){
                gasolineCars++;
            }
        }
    }
    /*
    public void sellCar(Car car){
        inventory.remove(car);
        if(car.getFuelType().equals("diesel")){
            dieselCars--;
        }
        else if(car.getFuelType().equals("gasoline")){
            gasolineCars--;
        }
    }
    */


    public void listInventory() {
        System.out.println(ColorConstants.RED+"Inventory:"+ ColorConstants.RESET);
        System.out.println();
        System.out.println(ColorConstants.YELLOW+"Gasoline:"+"("+gasolineCars+" cars)"+ ColorConstants.RESET);
        System.out.println();
        for (Car car : inventory) {
            if (car.getFuelType().equals("gasoline")){
                gasolineCars++;
                car.getCarDetails();
            }
        }
        System.out.println(ColorConstants.YELLOW+"Diesel:"+"("+dieselCars+" cars)"+ ColorConstants.RESET);
        System.out.println();
        for (Car car : inventory) {
            if (car.getFuelType().equals("diesel")){
                dieselCars++;
                //System.out.println(car);
                car.getCarDetails();
            }
        }
    }

    public void setDieselCars(int dieselCars) {
        this.dieselCars = dieselCars;
    }

    public void setGasolineCars(int gasolineCars) {
        this.gasolineCars = gasolineCars;
    }
}
