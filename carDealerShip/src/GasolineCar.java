public final class GasolineCar extends Car {
    public GasolineCar(String producer, String model, int year, double price, int kilometres) {
        super(producer, model, year, price, kilometres);
    }

    @Override
    public String getFuelType() {
        return "gasoline";
    }

    @Override
    public void getCarDetails() {
        System.out.println(ColorConstants.CYAN+"Producer: "+ColorConstants.RESET+this.getProducer());
        System.out.println(ColorConstants.CYAN+"Model: "+ColorConstants.RESET+this.getModel());
        System.out.println(ColorConstants.CYAN+"Year: "+ColorConstants.RESET+this.getYear());
        System.out.println(ColorConstants.CYAN+"Price: "+ColorConstants.RESET+"$"+this.getPrice());
        System.out.println(ColorConstants.CYAN+"Kilometres: "+ColorConstants.RESET+this.getKilometres());
        System.out.println(ColorConstants.CYAN+"Fuel: "+ColorConstants.RESET+" gasoline");
        System.out.println();
    }
}
